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
 * TCPServer
 * to start using it is needed to run method init() which returns bool result
 *
 * Usage: it's nothing you should do by yourself (there is a tread which works with answer clients requests)
 */

class TCPServer {
private:
    //server info
    uint16_t port;
    IPaddress ipAddress;
    TCPsocket tcpSocket;
    //storing clients connections
    SDLNet_SocketSet clientSocketSet;
    std::vector<std::unique_ptr<TCPClient> > clientConnections;
    //variables for server thread which checking for clients connections
    std::mutex server_mut;
    bool server_flag;
    std::thread server_tread;

    //preparing method
    bool setupPort();

    //preparing method
    bool openPortForListening();

    //if there is clients which wants to connect this method will accept new connection
    void acceptConnection();

    //check if any client sent request
    bool checkForRequests();

    //returns size of file
    int fileSize(const char *filename);

    //method for thread for server
    void serverManager();

    //sending file (with directory equal to file_dir) to client with unique id equal to number
    void sendFile(int number, std::string file_dir);

    //answers all clients requests
    void answerRequests();
public:
    //initializing with port of new server
    TCPServer(uint16_t port_);

    ~TCPServer();

    //method which preparing work of TCPServer class (if it returns false it cannot be used)
    bool init();

    //returns information about server as string
    std::string getInformation();
};

#endif