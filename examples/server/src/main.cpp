//
// Created by Vlad on 09.10.2016.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <thread>
#include <mutex>

#include "TCPClient.h"
#include "TCPServer.h"

TCPClient *client;
TCPServer *server;

std::string ip = "";
int port;
bool isServer;
bool server_flag = true;
std::mutex server_mut;

void GetSettingsFromUser();

void serverManager() {
    while(true) {
        server->acceptConnection();
        if(server->checkForRequests()) {
            server->answerRequests();
        }
        server_mut.lock();
        if (!server_flag) {
            server_mut.unlock();
            break;
        }
        server_mut.unlock();
    }
    std::cout << "leaving the tread\n";
}

int main(int argv, char **args) {
    if (SDLNet_Init() == -1) {
        std::cout << "Can't init\n";
        std::cout << SDLNet_GetError() << "\n";
    }
    GetSettingsFromUser();

    if (isServer) {
        server = new TCPServer(port);
    } else {
        client = new TCPClient(ip, port);
    }


    if (isServer) {
        server->setupPort();
        server->openPortForListening();
        std::thread server_tread(serverManager);
        while (true) {
            std::cout << "Choose one and hit enter : "
                      << "\n\ta -> accept connection"
                      << "\n\ti -> get information"
                      << "\n\ts -> send file"
                      << "\n\tc -> check for requests"
                      << "\n\tr -> answer requests"
                      << "\n\tq -> quit"
                              "\nYou choice : \n";
            char state;
            std::cin >> state;
            int number = 0;
            std::string fileName;
            switch (state) {
                case 'i':
                    server->getInformation();
                    break;
                case 's':
                    std::cout << "number of client:\n";
                    std::cin >> number;
                    std::cout << "file name:\n";
                    std::cin >> fileName;
                    server->sendFile(number, fileName);
                    break;
                case 'a':
                    server->acceptConnection();
                    break;
                case 'q':
                    server_mut.lock();
                    server_flag = false;
                    server_mut.unlock();
                    server_tread.join();
                    SDLNet_Quit();
                    return 0;
                case 'c':
                    std::cout << "checking for requests\n";
                    if (server->checkForRequests()) {
                        std::cout << "There are new requests!\n";
                    } else {
                        std::cout << "There isn't any new request\n";
                    }
                    std::cout << "==================================================\n";
                    break;
                case 'r':
                    std::cout << "trying to answer requests\n";
                    server->answerRequests();
                    break;
                default:
                    continue;
            }
        }
    } else {
        client->setupIpAddress();
        std::cout << "trying to connect\n";
        client->openConnectionToServer();
        int code;
        while (true) {
            std::cout << "Choose one and hit enter : "
                      << "\n\tr -> read file"
                      << "\n\ts -> sendRequest"
                      << "\n\tq -> quit"
                              "\nYou choice : \n";
            char state;
            std::cin >> state;
            switch (state) {
                case 'q':
                    client->close();
                    SDLNet_Quit();
                    return 0;
                case 'r':
                    client->readFile();
                    break;
                case 's':
                    code = 0;
                    std::cout
                            << "put request code for server (1 - get information in xml file, 2 - try to join the game):\n";
                    std::cin >> code;
                    std::cout << "trying to send request\n";
                    client->sendRequest(code);
                    break;
                default:
                    continue;
            }
        }
    }
}

void GetSettingsFromUser() {
    std::cout << "Is this a server? ( Type \'y\' for server, otherwise \'n\' and hit enter) : \n";
    char isServerInput = 'n';
    std::cin >> isServerInput;
    isServer = (isServerInput == 'y');

    if (!isServer) {
        std::cout << "Enter remote IP ( 127.0.0.1  for local connections ) : \n";
        std::cin >> ip;
    }

    std::cout << "Enter the port number ( this needs to be the same for server and client ) : \n";
    std::cin >> port;
    std::cout << "\nport: " << port << "\n";
    std::cout << "ip: " << ip << "\n\n";
}