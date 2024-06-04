#include "headers/game.h"

#include "headers/partida.h"

Game::Game(Queue<Command>& actionQueue, Queue<Contenedor>& stateQueue):
        actionQueue(actionQueue), stateQueue(stateQueue),clientCharactersMutex() {
}

void Game::run() {
    // Queue<Contenedor> q; // esta queue tiene que ir al sender
    Mapa m = Mapa();
    //Personaje personaje = Personaje(4, 0, 2, 4, 100, EntityType::JAZZ, AnimationType::WALK);
    //Enemigo enemigo = Enemigo(50, 4, 4, 8, 100, EntityType::ENEMY, AnimationType::WALK);
    //objetos.agregar_objeto(&personaje);
    //objetos.agregar_objeto(&enemigo);
    //entes.push_back(&personaje);
    //entes.push_back(&enemigo);



    while (_keep_running) {
        // uint32_t time1 = SDL_GetTicks();
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
            }
        }

       //std::cout << "Enemigo posx: "<< enemigo.x << " posy: " << enemigo.y << std::endl;
       if (clientCharacters.size() > 0)
       std::cout << "Personaje posx: "<< clientCharacters.begin()->second->x << " posy: " << clientCharacters.begin()->second->y << std::endl;


        objetos.eliminar_borrados(stateQueue);
        objetos.correr_colisiones();
        for (auto e: entes) {
            e->update_vivo(objetos, stateQueue);
        }
        objetos.update(m, stateQueue);

        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    }
}

void Game::addPlayer(int clientId) {
    std::lock_guard<std::mutex> lock(clientCharactersMutex);
    Personaje* personaje = new Personaje(4 + clientId * 20, 4, 4, 8, 100, EntityType::JAZZ, AnimationType::WALK);
    personaje->set_id(clientId);
    clientCharacters[clientId] = personaje;
    objetos.agregar_objeto(personaje);
    entes.push_back(personaje);
}



void Game::stop() {
    stateQueue.close();
    _is_alive = false;
    _keep_running = false;
}
