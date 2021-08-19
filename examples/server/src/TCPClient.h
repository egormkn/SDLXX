//
// Created by Vlad on 09.10.2016.
//

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <SDL_net.h>

class TCPClient {
private:
    bool isConnectedFlag = false;

    std::string ip;
    int32_t port;

    int32_t waitTime = 60000;

    // Holds the address and port to the server
    IPaddress ipAddress;
    TCPsocket tcpSocket;

public:
    TCPClient(const std::string &ip_, int32_t port_);

    TCPClient (TCPsocket newSocket);

    bool setupIpAddress();

    bool openConnectionToServer();

    void close();

    bool isConnected();

    void readFile();

    TCPsocket getSocket();

    void sendRequest(int request_code);
};
