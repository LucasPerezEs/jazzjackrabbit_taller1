#include "headers/server.h"

Server::Server(const char* servname): srv(servname) {}

void Server::run() {

    int c;

    std::list<ClientHandler*> clients;

    GamesManager game_manager;
    Acceptor thread_acceptador(srv, clients, game_manager);

    game_manager.start();
    thread_acceptador.start();

    do {
        c = getchar();
    } while (c != 'q');

    thread_acceptador.stop();
    game_manager.stop();


    thread_acceptador.join();
    std::cout << "thread_acceptador.join();" << std::endl;
    game_manager.join();
    std::cout << "game_manager.join();" << std::endl;
}
