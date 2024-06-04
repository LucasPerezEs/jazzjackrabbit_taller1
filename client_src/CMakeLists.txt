add_library(client_lib
    event_handler.cpp
    model_updater.cpp
    game.cpp
    protocol.cpp
    client.cpp
    clientReceiver.cpp
    entity.cpp
    ../common_src/liberror.cpp
    ../common_src/protocol.cpp
    ../common_src/resolver.cpp
    ../common_src/resolvererror.cpp
    ../common_src/socket.cpp
    ../server_src/contenedor.cpp
    sdl_libs/Animation.cpp
    sdl_libs/Area.cpp
    sdl_libs/Exception.cpp
    sdl_libs/SdlException.cpp
    sdl_libs/SdlTexture.cpp
    sdl_libs/SdlWindow.cpp
        setupscreen/ConnectMenu.cpp
)

target_link_libraries(client_lib setupscreen)
target_include_directories(client_lib PRIVATE headers/*)
target_include_directories(client_lib PRIVATE ../common_src/headers/* setupscreen)




