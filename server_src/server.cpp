#include "server_class.h"

Server::Server(const char* servname): srv(servname) {}

void Server::run() {

    int c;

    Queue<Command::ActionType> actionQueue;
    Queue<EnemyEvent> eventQueue;

    std::list<ClientHandler*> clients;


    Game game(actionQueue, eventQueue);
    Acceptor thread_acceptador(srv, clients, actionQueue);
    Broadcaster br(clients, eventQueue);


    game.start();
    thread_acceptador.start();
    br.start();


    do {
        c = getchar();
    } while (c != 'q');

    thread_acceptador.stop();

    game.stop();
    br.stop();

    thread_acceptador.join();
    game.join();
    br.join();
}
