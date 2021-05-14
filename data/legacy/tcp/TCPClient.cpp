#include "TCPClient.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>

#include <SDL_net.h>
#include <sdlxx/core/log.h>

TCPClient::TCPClient(const std::string &ip_, uint16_t port_) {
    ip = ip_;
    port = port_;
    sdlxx::net::Log::verbose("[TCPClient] created");
}

TCPClient::TCPClient(TCPsocket newSocket) {
    tcpSocket = newSocket;
    sdlxx::net::Log::verbose("[TCPClient] created");
}

TCPClient::~TCPClient() {
    isConnectedFlag = false;
    SDLNet_TCP_Close(tcpSocket);
    sdlxx::net::Log::verbose("[TCPClient] closed");
}

bool TCPClient::init() {
    return (setupIpAddress() && openConnectionToServer());
}

bool TCPClient::setupIpAddress() {
    int result = SDLNet_ResolveHost(&ipAddress, ip.c_str(), port);

    if (result == -1) {
        sdlxx::net::Log::warning("[TCPClient] failed to resolve host");
        return false;
    }

    sdlxx::net::Log::verbose("[TCPClient] host resolved");
    return true;
}

bool TCPClient::openConnectionToServer() {
    tcpSocket = SDLNet_TCP_Open(&ipAddress);

    if (tcpSocket == nullptr) {
        sdlxx::net::Log::warning("[TCPClient] failed to open connection:\n" + std::string(SDLNet_GetError()));
        return false;
    }

    isConnectedFlag = true;

    sdlxx::net::Log::verbose("[TCPClient] connection opened");
    return true;
}

bool TCPClient::isConnected() {
    return isConnectedFlag;
}

void TCPClient::readFile() {
    int buffer_size = 1024 * 128;
    char *buffer = new char[buffer_size];
    std::ofstream out("xml_for_client.xml", std::ifstream::binary);

    int32_t size = 0;
    SDLNet_TCP_Recv(tcpSocket, &size, 4);
    //std::cout << "summary size of packets: " << size << '\n';

    int bytes_achieved;
    int achieved_size = 0;

    while (achieved_size != size) {
        bytes_achieved = SDLNet_TCP_Recv(tcpSocket, buffer, buffer_size);
        achieved_size += bytes_achieved;
        //std::cout << "Received : " << bytes_achieved << " bytes\n";
        out.write(buffer, bytes_achieved > buffer_size ? buffer_size : bytes_achieved);
    }
    out.close();
    delete[] buffer;
    sdlxx::net::Log::verbose("[TCPClient] information successfully achieved");
}

TCPsocket TCPClient::getSocket() {
    return tcpSocket;
}

void TCPClient::sendRequest(int32_t request_code) {
    sdlxx::net::Log::debug("[TCPClient] trying to send request with code: " + std::to_string(request_code));
    SDLNet_TCP_Send(tcpSocket, &request_code, 4);
    if (request_code == 1) {
        readFile();
    }
}

void TCPClient::requestServerInformation() {
    sendRequest(1);
}

void TCPClient::requestForConnection() {
    sendRequest(2);
}

void TCPClient::resolveIp() {
    char *host = new char[4];
    SDLNet_Write32(ipAddress.host, &host);
    std::cout << "SDLNet_ResolveIP: " << (unsigned int) &host[0] << '.' << (unsigned int) &host[1] << '.' << (unsigned int) &host[2] << '.'
              << (unsigned int) &host[3] << '\n' <<
              "==================================================\n";
    delete[] host;
}
