add_library(server_lib
    enemigo.cpp
    game.cpp
    mapa.cpp
    objeto.cpp
    partida.cpp
    personaje.cpp
    protocol.cpp
    broadcaster.cpp
    client.cpp
    clientReceiver.cpp
    clientSender.cpp
    acceptor.cpp
    server.cpp
    contenedor.cpp
    lista_objetos.cpp
    municion.cpp
    pickup.cpp
    zanahoria.cpp
    gold_coin.cpp
    clock.cpp
    ghost.cpp
    bat.cpp
    ../common_src/liberror.cpp
    ../common_src/protocol.cpp
    ../common_src/resolver.cpp
    ../common_src/resolvererror.cpp
    ../common_src/socket.cpp
)

target_include_directories(server_lib PRIVATE headers/*)
target_include_directories(server_lib PRIVATE ../common_src/headers/*)