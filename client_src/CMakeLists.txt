add_library(client_lib
    event_handler.cpp
    model_updater.cpp
    game.cpp
    player.cpp
    protocol.cpp
    ../common_src/liberror.cpp
    ../common_src/protocol.cpp
    ../common_src/resolver.cpp
    ../common_src/resolvererror.cpp
    ../common_src/socket.cpp
    sdl_libs/Animation.cpp
    sdl_libs/Area.cpp
    sdl_libs/Exception.cpp
    sdl_libs/SdlException.cpp
    sdl_libs/SdlTexture.cpp
    sdl_libs/SdlWindow.cpp
        client.cpp
)

target_include_directories(client_lib PRIVATE headers/*)
target_include_directories(client_lib PRIVATE ../common_src/headers/*)