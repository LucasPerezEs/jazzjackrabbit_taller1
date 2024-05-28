#include "headers/game.h"

#include "headers/partida.h"

Game::Game(Queue<Command::ActionType>& actionQueue, Queue<Contenedor>& stateQueue):
        actionQueue(actionQueue), stateQueue(stateQueue) {}

void Game::run() {
    // Queue<Contenedor> q; // esta queue tiene que ir al sender
    Mapa m = Mapa();
    ListaObjetos objetos;
    std::vector<Ente*> entes;
    Personaje personaje = Personaje(4, 0, 2, 4, 100);
    Enemigo enemigo = Enemigo(50, 0, 2, 4, 100);
    objetos.agregar_objeto(&personaje);
    objetos.agregar_objeto(&enemigo);
    entes.push_back(&personaje);
    entes.push_back(&enemigo);


    while (_keep_running) {
        // uint32_t time1 = SDL_GetTicks();
        Command::ActionType command;
        while (actionQueue.try_pop(command)) {
            if (command == Command::LEFT) {
                personaje.moveLeft();
            } else if (command == Command::RIGHT) {
                personaje.moveRigth();
            } else if (command == Command::RUNFAST) {
                personaje.run();
            } else if (command == Command::JUMP) {
                personaje.jump();
            } else if (command == Command::FIRE) {
                personaje.disparando = true;
            } else if (command == Command::STOPLEFT) {
                personaje.stopMovingLeft();
            } else if (command == Command::STOPRIGHT) {
                personaje.stopMovingRight();
            } else if (command == Command::RUN) {
                personaje.stoprunning();
            } else if (command == Command::STOPFIRE) {
                personaje.disparando = false;
            }
        }

        objetos.eliminar_borrados(stateQueue);
        objetos.correr_colisiones();
        for (auto e: entes) {
            e->update_vivo(objetos, stateQueue);
        }
        objetos.update(m, stateQueue);

        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    }
}


void Game::stop() {
    stateQueue.close();
    _is_alive = false;
    _keep_running = false;
}
