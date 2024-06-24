add_library(client_lib
    event_handler.cpp
    model_updater.cpp
    game.cpp
    protocol.cpp
    client.cpp
    drawer.cpp
    clientReceiver.cpp
    entity.cpp
    player.cpp
    camara.cpp
    UIManager.cpp
    SoundManager.cpp
    ../common_src/liberror.cpp
    ../common_src/protocol.cpp
    ../common_src/resolver.cpp
    ../common_src/resolvererror.cpp
    ../common_src/socket.cpp
    ../common_src/Container.cpp
    sdl_libs/Animation.cpp
    sdl_libs/Area.cpp
    sdl_libs/Exception.cpp
    sdl_libs/SdlException.cpp
    sdl_libs/SdlTexture.cpp
    sdl_libs/SdlWindow.cpp
    sdl_libs/Fuente.cpp
    sdl_libs/Music.cpp
    sdl_libs/Sound.cpp
    setupscreen/ConnectMenu.cpp
)

target_link_libraries(client_lib setupscreen)
target_include_directories(client_lib PRIVATE headers/*)
target_include_directories(client_lib PRIVATE ../common_src/headers/* setupscreen)




