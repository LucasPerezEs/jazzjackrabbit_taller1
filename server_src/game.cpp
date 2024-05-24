#include "headers/game.h"

//Game::Game(const std::string& servname): servname(servname) {}


// Pre: -
// Post: Inicializa el contenedor de partidas y se prepará para recibir jugadores.
//void Game::init_game() {
//
//    bool server_closed = false;
//    /*
//    Aceptador acepta los jugadores y tiene la referencia a las partidas
//    para que estos decidan a cual unirse o si crear una.
//    */
//    Aceptador aceptador(servname, server_closed);
//    aceptador.start();
//
//    while (std::cin.get() != 'q') {}
//    server_closed = true;
//    aceptador.finalizar_conexion();
//    aceptador.join();
//}

Game::Game(Queue<Command::ActionType>& actionQueue, Queue<State::StateType>& stateQueue):
        actionQueue(actionQueue), stateQueue(stateQueue) {}

void Game::run() {

    while (_keep_running) {
        Command::ActionType command;
        if (actionQueue.try_pop(command)) {
            std::cout << "Comando recibido: " << command << std::endl;
            // Hago algo con el comando
        }

    }
}


void Game::stop() {
    stateQueue.close();
    _is_alive = false;
    _keep_running = false;
}