#include "headers/acceptor.h"


Acceptor::Acceptor(Socket& socket, std::list<ClientHandler*>& clients,
                   Queue<Command>& actionQueue, Game& game):
        sk(socket), clients(clients), actionQueue(actionQueue), game(game) {}

void Acceptor::reap_offline_clients() {
    clients.remove_if([](ClientHandler* c) {
        if (!c->is_online()) {
            c->kill();
            delete c;
            return true;
        }
        return false;
    });
}

void Acceptor::kill_all() {
    for (auto& c: clients) {
        if (c->is_online()) {
            c->kill();
        }
        delete c;
    }
    clients.clear();
}

void Acceptor::run() {
    int id = 0;
    while (_keep_running) {
        try {
            id++;
            Socket peer = sk.accept();
            ClientHandler* client = new ClientHandler(id,std::move(peer), actionQueue);
            client->go_online();
            clients.push_back(client);
            game.addPlayer(id);
            reap_offline_clients();
        } catch (LibError& err) {
            break;
        }
    }
    _is_alive = false;
}

void Acceptor::stop() {

    _keep_running = false;
    kill_all();
    sk.shutdown(SHUT_RDWR);
    sk.close();
}
