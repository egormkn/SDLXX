cmake_minimum_required(VERSION 3.6)

project(SDLgameserver)

message("Game Server")

add_executable(SDLgameserver src/main.cpp src/TCPClient.cpp src/TCPServer.cpp)
set_property(TARGET SDLgameserver PROPERTY CXX_STANDARD 11)

target_link_libraries(SDLgameserver
    TinyXML
    Logger
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    ${SDL2_NET_LIBRARY}
    ${SDL2_MIXER_LIBRARY})