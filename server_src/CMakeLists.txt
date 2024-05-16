add_library(server_lib
    aceptador.cpp
    enemigo.cpp
    game.cpp
    jugador.cpp
    mapa.cpp
    objeto.cpp
    partida.cpp
    personaje.cpp
    protocol.cpp
    servidor.cpp
    ../common_src/liberror.cpp
    ../common_src/protocol.cpp
    ../common_src/resolver.cpp
    ../common_src/resolvererror.cpp
    ../common_src/socket.cpp
)

target_include_directories(server_lib PRIVATE headers/*)
target_include_directories(server_lib PRIVATE ../common_src/headers/*)