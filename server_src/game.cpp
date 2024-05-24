#include "headers/game.h"

Game::Game(Queue<Command::ActionType>& actionQueue, Queue<State::StateType>& stateQueue):
        actionQueue(actionQueue), stateQueue(stateQueue) {}

void Game::run() {

    while (_keep_running) {
        Command::ActionType command;
        if (actionQueue.try_pop(command)) {
            std::cout << "Comando recibido: " << command << std::endl;
            // Hago algo con el comando
        }

        //LOGICA PRINCIPAL
        std::cout << "Pusheo estado de prueba " << command << std::endl;
        stateQueue.push(State::INTOXICATED);


        //NO HAY NADA BLOQUEANTE, ESTE SLEEP ES PARA QUE NO HAGA MIERDA EL CPU
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    }
}


void Game::stop() {
    stateQueue.close();
    _is_alive = false;
    _keep_running = false;
}