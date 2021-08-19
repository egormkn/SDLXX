//
// Created by Vlad on 09.10.2016.
//

/*
 * codes for connection requests:
 * 1 - get information
 * 2 - try to connect to the server
 */

#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <SDL_net.h>
#include "TCPClient.h"

class TCPServer {
private:
    int32_t port;
    IPaddress ipAddress;
    TCPsocket tcpSocket;
    SDLNet_SocketSet clientSocketSet;
    std::vector<std::unique_ptr<TCPClient> > clientConnections;

    int fileSize(const char *filename);

public:
    TCPServer(int32_t port_);

    ~TCPServer();

    bool setupPort();

    bool openPortForListening();

    bool canAcceptConnection();

    void acceptConnection();

    bool checkForRequests();

    void getInformation();

    void sendFile(int number, std::string file_dir);

    void answerRequests();
};
