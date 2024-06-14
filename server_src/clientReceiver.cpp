#include "headers/clientReceiver.h"

// cppcheck-suppress uninitMemberVar
ClientReceiver::ClientReceiver(uint32_t id, ServerProtocol& protocol):
        id(id), serverProtocol(protocol) {}

void ClientReceiver::run() {
    bool joined = false;
    while (_keep_running) {
        try {
            // recibir comando de un cliente
            auto action = serverProtocol.receive_command();
            // std::cout << "action:"  << action << std::endl;
            if (action == Command::CREATE_GAME) {
                create_game();
            } else if (action == Command::JOIN_GAME) {
                join_game(joined);
            } else if (action == Command::GET_GAME_LIST) {
                // std::cout << "GET_GAME_LIST" << std::endl;
            } else {
                Command command = {action, id};
                queueReceiver->push(command);
            }
        } catch (ProtocolDesconection& d) {
            break;
        } catch (LibError& e) {
            break;
        } catch (ClosedQueue& c) {
            break;
        }
    }

    stop();
    _is_alive = false;
}

void ClientReceiver::join_game(bool& joined) {
    // cppcheck-suppress unreadVariable
    std::string gameID = serverProtocol.receive_game_id();
    // std::cout << "join_game ID :" << gameID << std::endl;
    joined = true;
}

void ClientReceiver::create_game() {
    // cppcheck-suppress unreadVariable
    std::string gameID = serverProtocol.receive_game_id();
    // std::cout << "create_game ID :" << gameID << std::endl;
    // uint32_t max_players = serverProtocol.receive_max_players();
    // games.createGame(gameID, max_players);
}

void ClientReceiver::send_game_list() {
    // std::vector<std::string> gameIDs = games.getGamesIDs();
    // serverProtocol.send_games_ids(gameIDs);
}

void ClientReceiver::setQueue(Queue<Command>* queue) { queueReceiver = queue; }
