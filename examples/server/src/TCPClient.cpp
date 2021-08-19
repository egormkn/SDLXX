//
// Created by Vlad on 09.10.2016.
//

#include "TCPClient.h"
#include <iostream>
#include <ostream>
#include <memory>
#include <fstream>
#include <SDL_net.h>

TCPClient::TCPClient(const std::string &ip_, int32_t port_) {
    ip = ip_;
    port = port_;
    std::cout << "CLIENT created\n" <<
              "==================================================\n";
}

TCPClient::TCPClient(TCPsocket newSocket) {
    tcpSocket = newSocket;
    std::cout << "CLIENT for server created\n" <<
              "==================================================\n";
}

bool TCPClient::setupIpAddress() {
    std::cout << "Trying to initialize\n";
    int result = SDLNet_ResolveHost(&ipAddress, ip.c_str(), port);

    if (result == -1) {
        std::cout << "ERROR: Failed to resolve host\n" <<
                  "==================================================\n";
        return false;
    }

    std::cout << "Host resolved\n" <<
              "==================================================\n";
    return true;
}

bool TCPClient::openConnectionToServer() {
    std::cout << "Opening connection\n";

    tcpSocket = SDLNet_TCP_Open(&ipAddress);

    if (tcpSocket == nullptr) {
        std::cout << "ERROR: Failed to open connection:\n" << SDLNet_GetError() << "\n" <<
                  "==================================================\n";
        return false;
    }

    isConnectedFlag = true;

    std::cout << "Connection opened!\n" <<
              "==================================================\n";

    return true;
}

void TCPClient::close() {
    isConnectedFlag = false;
    std::cout << "Closing connection\n" <<
              "==================================================\n";
    SDLNet_TCP_Close(tcpSocket);
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
    std::cout << "summary size of packets: " << size << '\n';

    int bytes_achieved;
    int achieved_size = 0;

    while (achieved_size != size) {
        bytes_achieved = SDLNet_TCP_Recv(tcpSocket, buffer, buffer_size);
        achieved_size += bytes_achieved;
        std::cout << "Received : " << bytes_achieved << " bytes\n";
        out.write(buffer, bytes_achieved > buffer_size ? buffer_size : bytes_achieved);
    }
    out.close();
    delete[] buffer;
    std::cout << "Information successfully achieved!\n" <<
              "==================================================\n";
}

TCPsocket TCPClient::getSocket() {
    return tcpSocket;
}

void TCPClient::sendRequest(int32_t request_code) {
    std::cout << "Trying to send request with code: " << request_code << "\n";
    SDLNet_TCP_Send(tcpSocket, &request_code, 4);
    if (request_code == 1) {
        std::cout << "Waiting for information from server\n";
        readFile();
    }
}