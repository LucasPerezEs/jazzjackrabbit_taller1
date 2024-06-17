#include "headers/game.h"

#include "headers/partida.h"

Game::Game(Queue<Message>& actionQueue, Queue<Container>& stateQueue, uint32_t maxPlayers,
           std::map<std::string, float>& config):
        maxPlayers(maxPlayers),
        actionQueue(actionQueue),
        stateQueue(stateQueue),
        config(config),
        clientCharactersMutex(),
        clock(config),
        gameStarted(false) {}

void Game::run() {
    // Queue<Contenedor> q; // esta queue tiene que ir al sender
    Mapa m = Mapa();
    Ghost ghost = Ghost(50, 2, config);
    Bat bat = Bat(75, 4, config);
    Monkey monkey = Monkey(20, 1, config);
    objetos.agregar_objeto(&ghost);
    objetos.agregar_objeto(&bat);
    objetos.agregar_objeto(&monkey);
    entes.push_back(&ghost);
    entes.push_back(&bat);
    // cppcheck-suppress danglingLifetime
    entes.push_back(&monkey);

    while (_keep_running && !clock.times_up()) {
        Message msg(Command::ActionType::NONE);
        while (actionQueue.try_pop(msg)) {
            uint32_t clientId = msg.id();
            Personaje* personaje = clientCharacters[clientId];

            switch (msg.command.action) {
                case Command::ActionType::LEFT:
                    personaje->moveLeft();
                    break;
                case Command::ActionType::RIGHT:
                    personaje->moveRigth();
                    break;
                case Command::ActionType::RUNFAST:
                    personaje->run();
                    break;
                case Command::ActionType::JUMP:
                    personaje->jump();
                    break;
                case Command::ActionType::SPECIAL:
                    personaje->special_action();
                    break;
                case Command::ActionType::FIRE:
                    personaje->disparando = true;
                    break;
                case Command::ActionType::STOPLEFT:
                    personaje->stopMovingLeft();
                    break;
                case Command::ActionType::STOPRIGHT:
                    personaje->stopMovingRight();
                    break;
                case Command::ActionType::RUN:
                    personaje->stoprunning();
                    break;
                case Command::ActionType::STOPFIRE:
                    personaje->disparando = false;
                    break;
                case Command::ActionType::QUIT:
                    personaje->borrar = true;
                    break;
                default:
                    break;
            }
        }
        objetos.eliminar_borrados(stateQueue);
        objetos.correr_colisiones();
        for (auto e: entes) {
            e->update_vivo(objetos, stateQueue, clientCharacters);
        }
        objetos.update(m, stateQueue);

        clock.update(stateQueue);

        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    }
}


void Game::addPlayer(uint32_t clientId) {
    std::lock_guard<std::mutex> lock(clientCharactersMutex);

    Container init(2, clientId, 0, 0, 0, 0, 0, AnimationType::NONE_ANIMATION,
                  EntityType::NONE_ENTITY, 0, 0, 0);
    stateQueue.push(init);
    Lori* lori = new Lori(20 + clientId, 2, config);
    lori->set_id(clientId);
    clientCharacters[clientId] = lori;
    objetos.agregar_objeto(lori);
    entes.push_back(lori);

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
