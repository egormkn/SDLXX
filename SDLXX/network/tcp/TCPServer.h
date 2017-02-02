#ifndef SDLXX_TCPSERVER_H
#define SDLXX_TCPSERVER_H

#include <string>
#include <memory>
#include <iostream>
#include <SDL_net.h>
#include "TCPClient.h"
#include <mutex>
#include <thread>

/*
 * codes for connection requests:
 * 1 - get information
 * 2 - try to connect to the server
 */

class TCPServer {
private:
    //server info
    int32_t port;
    IPaddress ipAddress;
    TCPsocket tcpSocket;
    //storing clients connections
    SDLNet_SocketSet clientSocketSet;
    std::vector<std::unique_ptr<TCPClient> > clientConnections;
    //variables for server thread which checking for clients connections
    std::mutex server_mut;
    bool server_flag;
    std::thread server_tread;

    int fileSize(const char *filename);

    void serverManager();

public:
    TCPServer(int32_t port_);

    ~TCPServer();

    bool init();

    bool setupPort();

    bool openPortForListening();

    bool canAcceptConnection();

    void acceptConnection();

    bool checkForRequests();

    std::string getInformation();

    void sendFile(int number, std::string file_dir);

    void answerRequests();
};

#endif