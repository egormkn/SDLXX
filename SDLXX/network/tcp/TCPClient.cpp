#include "TCPClient.h"
#include <iostream>
#include <ostream>
#include <memory>
#include <fstream>
#include <SDL_net.h>
#include "../../Log.h"


TCPClient::TCPClient(const std::string &ip_, int32_t port_) {
    ip = ip_;
    port = port_;
    SDLXX::Log::verbose("[TCPClient] created");
}

TCPClient::TCPClient(TCPsocket newSocket) {
    tcpSocket = newSocket;
    SDLXX::Log::verbose("[TCPClient] created");
}

TCPClient::~TCPClient() {
    isConnectedFlag = false;
    SDLNet_TCP_Close(tcpSocket);
    SDLXX::Log::verbose("[TCPClient] closed");
}

bool TCPClient::setupIpAddress() {
    //std::cout << "Trying to initialize\n";
    int result = SDLNet_ResolveHost(&ipAddress, ip.c_str(), port);

    if (result == -1) {
        SDLXX::Log::warning("[TCPClient] failed to resolve host");
        return false;
    }

    SDLXX::Log::verbose("[TCPClient] host resolved");
    return true;
}

bool TCPClient::openConnectionToServer() {
    //std::cout << "Opening connection\n";

    tcpSocket = SDLNet_TCP_Open(&ipAddress);

    if (tcpSocket == nullptr) {
        SDLXX::Log::warning("[TCPClient] failed to open connection:\n" + std::string(SDLNet_GetError()));
        return false;
    }

    isConnectedFlag = true;

    SDLXX::Log::verbose("[TCPClient] connection opened");
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
    SDLXX::Log::verbose("[TCPClient] information successfully achieved");
}

TCPsocket TCPClient::getSocket() {
    return tcpSocket;
}

void TCPClient::sendRequest(int32_t request_code) {
    SDLXX::Log::debug("[TCPClient] trying to send request with code: " + std::to_string(request_code));
    SDLNet_TCP_Send(tcpSocket, &request_code, 4);
    if (request_code == 1) {
        //std::cout << "Waiting for information from server\n";
        readFile();
    }
}

void TCPClient::resolveIp() {
    char *host = new char[4];
    SDLNet_Write32(ipAddress.host, &host);
    std::cout << "SDLNet_ResolveIP: " << (unsigned int) &host[0] << '.' << (int) &host[1] << '.' << (int) &host[2] << '.'
              << (int) &host[3] << '\n' <<
              "==================================================\n";
    delete[] host;
}