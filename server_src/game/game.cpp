#include "../headers/game.h"

#include <algorithm>

#include "../headers/broadcaster.h"

// cppcheck-suppress uninitMemberVar
Game::Game(Queue<Message>& actionQueue, Queue<Container>& stateQueue, uint32_t maxPlayers,
           // cppcheck-suppress passedByValue
           std::map<std::string, float> config, Broadcaster& broadcaster, bool& gameStarted, bool& gameEnded):
        maxPlayers(maxPlayers),
        actionQueue(actionQueue),
        stateQueue(stateQueue),
        config(config),
        broadcaster(broadcaster),
        clientCharactersMutex(),
        clock(config),
        gameStarted(gameStarted),
        gameEnded(gameEnded) {}

void Game::run() {

    gameStarted= true;

    Mapa m;
    std::shared_ptr<Ghost> ghost(new Ghost(50, 2, config));
    std::shared_ptr<Bat> bat(new Bat(75, 4, config));
    std::shared_ptr<Monkey> monkey(new Monkey(15, 1, config));
    objetos.agregar_objeto(ghost);
    objetos.agregar_objeto(bat);
    objetos.agregar_objeto(monkey);
    entes.push_back(ghost);
    entes.push_back(bat);
    entes.push_back(monkey);

    clock.start();

    Container c = Container(5, 0, 0, 0, 0, 0, 0, NONE_ANIMATION, NONE_ENTITY, 0,
                            {EntityType::NONE_ENTITY, 0}, 0, "");
    stateQueue.push(c);

    while (_keep_running && !clock.times_up()) {
        Message msg(Command::ActionType::NONE);
        while (actionQueue.try_pop(msg)) {
            uint32_t clientId = msg.id();
            std::shared_ptr<Personaje> personaje = clientCharacters[clientId];

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
                case Command::ActionType::CHANGE_AMMO:
                    personaje->change_selected_ammo();
                    break;
                case Command::ActionType::QUIT: {
                    // cppcheck-suppress shadowVariable
                    Container c(1, clientId, 0, 0, 0, 0, 0, AnimationType::NONE_ANIMATION,
                                EntityType::NONE_ENTITY, 0, {EntityType::NONE_ENTITY, 0}, 0, "");
                    stateQueue.push(c);
                    entes.erase(std::remove_if(entes.begin(), entes.end(),
                                               [&](std::shared_ptr<Ente> o) {
                                                   if (o->id == (int)clientId) {
                                                       return true;
                                                   }
                                                   return false;
                                               }));
                    clientCharacters.erase(clientId);
                    objetos.borrar(clientId);
                    broadcaster.erase_client(clientId);
                    break;
                }
                default:
                    break;
            }
        }
        objetos.eliminar_borrados(stateQueue);
        objetos.correr_colisiones();
        for (auto e: entes) {
            e->update_vivo(objetos, stateQueue, clientCharacters, e);
        }
        objetos.update(m, stateQueue);

        clock.update(stateQueue);

        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    }
    if (clock.times_up()) {
        // cppcheck-suppress shadowVariable
        Container c(2, -1, 0, 0, 0, 0, 0, AnimationType::NONE_ANIMATION, EntityType::NONE_ENTITY, 0,
                    {EntityType::NONE_ENTITY, 0}, 0, "");
        stateQueue.push(c);
        for (auto client: clientCharacters) {
            // clientCharacters.erase(client.first);
            // objetos.borrar(client.first);
            broadcaster.erase_client(client.first);
        }
    }
    gameEnded = true;
    _is_alive = false;
}

void Game::addPlayer(uint32_t clientId, uint32_t character, std::string name) {
    std::lock_guard<std::mutex> lock(clientCharactersMutex);

    if (character == 0) {
        std::shared_ptr<Jazz> personaje(new Jazz(20 + clientId, 10, config, stateQueue, name));
        personaje->set_id(clientId);
        clientCharacters[clientId] = personaje;
        objetos.agregar_objeto(personaje);
        entes.push_back(personaje);
    } else if (character == 1) {
        std::shared_ptr<Lori> personaje(new Lori(20 + clientId, 10, config, stateQueue, name));
        personaje->set_id(clientId);
        clientCharacters[clientId] = personaje;
        objetos.agregar_objeto(personaje);
        entes.push_back(personaje);
    } else {
        std::shared_ptr<Spaz> personaje(new Spaz(20 + clientId, 10, config, stateQueue, name));
        personaje->set_id(clientId);
        clientCharacters[clientId] = personaje;
        objetos.agregar_objeto(personaje);
        entes.push_back(personaje);
    }

    // Para mas adelante, el reloj deberia empezar cuando hay dos jugadores
    /*if (clientCharacters.size() == 1) {
        clock.start();
    }*/
}

void Game::stop() {
    stateQueue.close();
    _is_alive = false;
    _keep_running = false;
}

Game::~Game() {
    std::cout << "destruyendo\n";
    objetos.borrar();
    entes.clear();
}
