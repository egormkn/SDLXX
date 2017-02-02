#include <SDL_net.h>
#include <fstream>
#include "TCPServer.h"
#include <thread>
#include "../../Log.h"

int TCPServer::fileSize(const char *filename) {
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return (int) in.tellg();
}

void TCPServer::serverManager() {
    SDLXX::Log::debug("[TCPServer] server thread started");
    while (true) {
        //if (canAcceptConnection()) {
            acceptConnection();
        //}
        if (checkForRequests()) {
            answerRequests();
        }
        server_mut.lock();
        if (!server_flag) {
            server_mut.unlock();
            break;
        }
        server_mut.unlock();
    }
    SDLXX::Log::verbose("[TCPServer] thread closed");
}

TCPServer::TCPServer(uint16_t port_) {
    clientSocketSet = SDLNet_AllocSocketSet(10);
    port = port_;
    server_flag = true;
    SDLXX::Log::verbose("[TCPServer] created with port :" + std::to_string(port));
}

TCPServer::~TCPServer() {
    server_mut.lock();
    server_flag = false;
    server_mut.unlock();
    server_tread.join();
    SDLNet_FreeSocketSet(clientSocketSet);
    SDLXX::Log::verbose("[TCPServer] closed");
}

bool TCPServer::init() {
    if (!setupPort() || !openPortForListening()) {
        return false;
    }
    std::thread thread2(serverManager, this);
    server_tread.swap(thread2);
    return true;
}

bool TCPServer::setupPort() {
    int result = SDLNet_ResolveHost(&ipAddress, nullptr, port);

    if (result == -1) {
        SDLXX::Log::warning("[TCPServer] failed to resolve port");
        return false;
    }

    SDLXX::Log::verbose("[TCPServer] port resolved");
    return true;
}

bool TCPServer::openPortForListening() {
    //std::cout << "Opening connection\n";

    tcpSocket = SDLNet_TCP_Open(&ipAddress);

    if (tcpSocket == nullptr) {
        SDLXX::Log::warning("[TCPServer] failed opening port for listening");
        return false;
    }

    SDLXX::Log::verbose("[TCPServer] port opened for listening");
    return true;
}

void TCPServer::acceptConnection() {
    TCPsocket newSocket = SDLNet_TCP_Accept(tcpSocket);

    if (newSocket == nullptr) {
        //SDLXX::Log::warning("[TCPServer] cannot accept TCP connection: " + std::string(SDLNet_GetError()));
        return;
    }

    std::unique_ptr<TCPClient> connection(new TCPClient(newSocket));
    SDLNet_TCP_AddSocket(clientSocketSet, newSocket);
    clientConnections.push_back(std::move(connection));

    SDLXX::Log::debug("[TCPServer] connection accepted");
}

bool TCPServer::checkForRequests() {
    return SDLNet_CheckSockets(clientSocketSet, 3) != 0;
}

std::string TCPServer::getInformation() {
    return "Information about server:\nport: " + std::to_string(port) + "\nNumber of clients: " +
           std::to_string(clientConnections.size());
}

void TCPServer::sendFile(int number, std::string file_dir) {
    if (number >= clientConnections.size()) {
        SDLXX::Log::warning("[TCPServer] No client with such number: " + std::to_string(number));
    }
    TCPsocket socket = clientConnections[number]->getSocket();
    int buffer_size = 1024 * 128;

    int32_t size = fileSize(file_dir.c_str());
    SDLNet_TCP_Send(socket, &size, 4);
    //std::cout << "summary size of packets: " << size << '\n';

    //std::cout << "Starting sending file!\n";
    char *buffer = new char[buffer_size];
    std::ifstream in;
    in.open(file_dir.c_str(), std::ifstream::binary);
    int bytes_send = 0;
    int messageSize = 0;
    //std::cout << "Sending file:" << file_dir << "\n";
    while (in) {
        in.read(buffer, buffer_size);
        messageSize = in.gcount();
        bytes_send = SDLNet_TCP_Send(socket, buffer, messageSize);

        //std::cout << "Tried to send " << messageSize << "\tsent : " << bytes_send << "\n";
        if (bytes_send < messageSize) {
            std::cout << "\tSend failed : " << SDLNet_GetError() << "\n";
            SDLXX::Log::debug("[TCPServer] file send failed");
            break;
        }
    }
    SDLXX::Log::debug("[TCPServer] information successfully sent");
    delete[] buffer;
    in.close();
}

void TCPServer::answerRequests() {
    int activityCounter = SDLNet_CheckSockets(clientSocketSet, 0);
    if (activityCounter == 0) {
        //std::cout << "There is no requests for this server\n" <<
        //          "==================================================\n";
        return;
    }
    int i = 0;
    int result = 0;
    int32_t code_request = 0;
    TCPsocket socket;
    while (activityCounter > 0) {
        socket = clientConnections[i]->getSocket();
        if (!SDLNet_SocketReady(socket)) {
            ++i;
            continue;
        }
        --activityCounter;
        result = SDLNet_TCP_Recv(socket, &code_request, 4);
        if (result <= 0) {
            //std::cout << "result of receiving request: " << result <<
            //          "\nClient with current index " << i << " may be dead, so it is deleting\n";

            int numused = SDLNet_TCP_DelSocket(clientSocketSet, clientConnections[i]->getSocket());
            if (numused < 0) {
                SDLXX::Log::warning("[TCPServer] cannot delete " + std::to_string(i) + " client from set: " +
                                    std::string(SDLNet_GetError()));
            }
            clientConnections.erase(clientConnections.begin() + i);
            code_request = -1;
        }

        switch (code_request) {
            case -1:
                break;
            case 1:
                //std::cout << "Sending information about server to " << i << " client\n";
                sendFile(i, "info.xml");
                break;
            case 2:
                SDLXX::Log::debug("[TCPServer] " + std::to_string(i) + " client wants to join the game");
                //TODO: write joining the game
                break;
                //std::cout << "ERROR: unknown request code received from " << i << " client\n" <<
                //          "==================================================\n";
        }
        ++i;
        if (activityCounter == 0) {
            activityCounter = SDLNet_CheckSockets(clientSocketSet, 0);
            i = 0;
        }
    }
}