#include <iostream>
#include <sstream>
#include <vector>
#include <thread>
#include <mutex>

#include "TCPClient.h"
#include "TCPServer.h"
#include "../../Log.h"

TCPClient *client;
TCPServer *server;

std::string ip = "";
uint16_t port;
bool isServer;

void GetSettingsFromUser();

int main(int argv, char **args) {
    SDLXX::Log::debugMode(true);
    if (SDLNet_Init() == -1) {
        std::cout << "Can't init\n";
        std::cout << SDLNet_GetError() << "\n";
        return 0;
    }
    GetSettingsFromUser();

    if (isServer) {
        server = new TCPServer(port);
    } else {
        client = new TCPClient(ip, port);
    }


    if (isServer) {
        if (server->init()) {
            SDLXX::Log::debug("server init");
        } else {
            delete server;
            SDLNet_Quit();
            return 0;
        }
        while (true) {
            std::cout << "Choose one and hit enter : "
                      << "\n\ti -> get information"
                      << "\n\tq -> quit"
                              "\nYou choice : \n";
            char state;
            std::cin >> state;
            std::string fileName;
            switch (state) {
                case 'i':
                std::cout << server->getInformation();
                    break;
                case 'q':
                    delete server;
                    SDLNet_Quit();
                    return 0;
                default:
                    continue;
            }
        }
    } else {
        if (client->init()) {
            SDLXX::Log::debug("client init");
        } else {
            delete client;
            SDLNet_Quit();
            return 0;
        }
        while (true) {
            std::cout << "Choose one and hit enter : "
                      << "\n\ts -> server info"
                      << "\n\tj -> join"
                      << "\n\tq -> quit"
                      << "\n\ti - resolve ip"
                              "\nYou choice : \n";
            char state;
            std::cin >> state;
            switch (state) {
                case 'i':
                    client->resolveIp();
                    break;
                case 'q':
                    delete client;
                    SDLNet_Quit();
                    return 0;
                case 's':
                    client->requestServerInformation();
                    break;
                case 'j':
                    client->requestForConnection();
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