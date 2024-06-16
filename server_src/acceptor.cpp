#include "headers/acceptor.h"

Acceptor::Acceptor(Socket& socket, std::list<ClientHandler*>& clients, GamesManager& game_manager):
        sk(socket), clients(clients), gameManager(game_manager) {}

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

    uint32_t id = 1;
    while (_keep_running) {
        try {
            Socket peer = sk.accept();
            ClientHandler* client = new ClientHandler(id, std::move(peer));
            client->go_online();
            clients.push_back(client);
            gameManager.addClient(id,client);
            reap_offline_clients();
            id++;
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
