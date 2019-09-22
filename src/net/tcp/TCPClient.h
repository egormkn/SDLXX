#ifndef SDLXX_TCPCLIENT_H
#define SDLXX_TCPCLIENT_H

#include <iostream>
#include <vector>
#include <string>
#include <SDL_net.h>
#include <sdlxx/core/Log.h>

/*
 * TCPClient
 * to start using it is needed to run method init() which returns bool result
 *
 * Usage: requestServerInformation
 *        requestForConnection
 */

class TCPClient {
private:
    bool isConnectedFlag = false;
    std::string ip;
    uint16_t port;

    // Holds the address and port to the server
    IPaddress ipAddress;
    TCPsocket tcpSocket;

    //reading file with server information
    void readFile();

    /*
     * sends request to server with special code
     * codes for connection requests:
     * 1 - get information
     * 2 - try to connect to the server
     */
    void sendRequest(int request_code);

    //preparing method
    bool setupIpAddress();

    //preparing method
    bool openConnectionToServer();
public:
    //initializing with ip and port of server which you want connect to
    TCPClient(const std::string &ip_, uint16_t port_);

    //initializing wit ready socket (this is for server's clients)
    TCPClient (TCPsocket newSocket);

    ~TCPClient();

    //method which preparing work of TCPClient class (if it returns false it cannot be used)
    bool init();

    //returns stasus of connection
    bool isConnected();

    //returns socket
    TCPsocket getSocket();

    //request server to send xml file wit its information
    void requestServerInformation();

    //try to join game
    void requestForConnection();

    //debug method to put client information in console
    void resolveIp();
};

#endif
