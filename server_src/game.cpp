#include "headers/game.h"

#include "headers/partida.h"

Game::Game(Queue<Command>& actionQueue, Queue<Contenedor>& stateQueue,
           std::map<std::string, float>& config):
        actionQueue(actionQueue),
        stateQueue(stateQueue),
        config(config),
        clientCharactersMutex(),
        clock(config) {}

void Game::run() {
    // Queue<Contenedor> q; // esta queue tiene que ir al sender
    Mapa m = Mapa();
    Ghost ghost = Ghost(50, 2, config);
    Bat bat = Bat(75, 4, config);
    objetos.agregar_objeto(&ghost);
    objetos.agregar_objeto(&bat);
    entes.push_back(&ghost);
    // cppcheck-suppress danglingLifetime
    entes.push_back(&bat);


    while (_keep_running && !clock.times_up()) {
        Command command;
        while (actionQueue.try_pop(command)) {

            uint32_t clientId = command.clientId;
            Personaje* personaje = clientCharacters[clientId];

            if (command.action == Command::ActionType::LEFT) {
                personaje->moveLeft();
            } else if (command.action == Command::ActionType::RIGHT) {
                personaje->moveRigth();
            } else if (command.action == Command::ActionType::RUNFAST) {
                personaje->run();
            } else if (command.action == Command::ActionType::JUMP) {
                personaje->jump();
            } else if (command.action == Command::ActionType::SPECIAL) {
                personaje->special_action();
            } else if (command.action == Command::ActionType::FIRE) {
                personaje->disparando = true;
            } else if (command.action == Command::ActionType::STOPLEFT) {
                personaje->stopMovingLeft();
            } else if (command.action == Command::ActionType::STOPRIGHT) {
                personaje->stopMovingRight();
            } else if (command.action == Command::ActionType::RUN) {
                personaje->stoprunning();
            } else if (command.action == Command::ActionType::STOPFIRE) {
                personaje->disparando = false;
            } else if (command.action == Command::ActionType::QUIT) {
                personaje->borrar = true;
            }
        }

        objetos.eliminar_borrados(stateQueue);
        objetos.correr_colisiones();
        for (auto e: entes) {
            e->update_vivo(objetos, stateQueue);
        }
        objetos.update(m, stateQueue);

        clock.update(stateQueue);

        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    }
}

void Game::addPlayer(int clientId) {
    std::lock_guard<std::mutex> lock(clientCharactersMutex);
    Personaje* personaje = new Personaje(4 + clientId * 20, 2, 2, 4, EntityType::JAZZ,
                                         AnimationType::SHOOT_IDLE, config);
    personaje->set_id(clientId);
    clientCharacters[clientId] = personaje;
    objetos.agregar_objeto(personaje);
    entes.push_back(personaje);

    // Para mas adelante, el reloj deberia empezar cuando hay dos jugadores
    if (clientCharacters.size() == 1) {
        clock.start();
    }
}

void Game::stop() {
    stateQueue.close();
    _is_alive = false;
    _keep_running = false;
}
