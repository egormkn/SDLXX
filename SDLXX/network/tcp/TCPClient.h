#ifndef SDLXX_TCPCLIENT_H
#define SDLXX_TCPCLIENT_H

#include <iostream>
#include <vector>
#include <string>
#include <SDL_net.h>
#include "../../Log.h"

class TCPClient {
private:
    bool isConnectedFlag = false;
    std::string ip;
    int32_t port;

    // Holds the address and port to the server
    IPaddress ipAddress;
    TCPsocket tcpSocket;

public:
    TCPClient(const std::string &ip_, int32_t port_);

    TCPClient (TCPsocket newSocket);

    ~TCPClient();

    bool setupIpAddress();

    bool openConnectionToServer();

    bool isConnected();

    void readFile();

    TCPsocket getSocket();

    void sendRequest(int request_code);

    void resolveIp();
};

#endif