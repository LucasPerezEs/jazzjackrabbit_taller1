#include "../headers/game.h"

#include <algorithm>
#include <tuple>

#include "../headers/broadcaster.h"

// cppcheck-suppress uninitMemberVar
Game::Game(Queue<Message>& actionQueue, Queue<Container>& stateQueue, uint32_t maxPlayers,
           const std::string& mapName,
           // cppcheck-suppress passedByValue
           std::map<std::string, float> config, Broadcaster& broadcaster, bool& gameStarted,
           bool& gameEnded):
        maxPlayers(maxPlayers),
        mapName(mapName),
        actionQueue(actionQueue),
        stateQueue(stateQueue),
        config(config),
        broadcaster(broadcaster),
        clientCharactersMutex(),
        clock(config),
        gameStarted(gameStarted),
        gameEnded(gameEnded) {}

void Game::run() {

    gameStarted = true;
    Map m(mapName);

    clock.start();

    Container c = Container(5, 0, 0, 0, 0, 0, 0, NONE_ANIMATION, NONE_ENTITY, 0,
                            {EntityType::NONE_ENTITY, 0}, 0, "");
    stateQueue.push(c);


    for (auto objeto: m.spawnsOtros) {
        if (objeto[0] == 1) {
            // cppcheck-suppress shadowVariable
            std::shared_ptr<Monkey> m(new Monkey(objeto[2], objeto[1], config));
            objetos.agregar_objeto(m);
            entes.emplace_back(m);
        } else if (objeto[0] == 2) {
            std::shared_ptr<Ghost> g(new Ghost(objeto[2], objeto[1], config));
            objetos.agregar_objeto(g);
            entes.emplace_back(g);
        } else if (objeto[0] == 3) {
            std::shared_ptr<Bat> b(new Bat(objeto[2], objeto[1], config));
            objetos.agregar_objeto(b);
            entes.emplace_back(b);
        } else if (objeto[0] == 4) {
            std::shared_ptr<Gem> b(new Gem(objeto[2], objeto[1], config, stateQueue));
            objetos.agregar_objeto(b);
            // cppcheck-suppress shadowVariable
            Container c(0, b->id, b->x, b->y, b->width, b->height, 0, b->an_type, b->en_type, 0,
                        {EntityType::NONE_ENTITY, 0}, 0, "");
            stateQueue.push(c);
        } else if (objeto[0] == 5) {
            std::shared_ptr<Gold_Coin> b(new Gold_Coin(objeto[2], objeto[1], config, stateQueue));
            objetos.agregar_objeto(b);
            // cppcheck-suppress shadowVariable
            Container c(0, b->id, b->x, b->y, b->width, b->height, 0, b->an_type, b->en_type, 0,
                        {EntityType::NONE_ENTITY, 0}, 0, "");
            stateQueue.push(c);
        }
    }

    for (auto ente: entes) {

        std::vector<int> vector_spawn = m.get_spawn(ente->spawn);
        if (vector_spawn[0] == -1) {
            continue;
        }
        ente->x = vector_spawn[0];
        ente->y = vector_spawn[1];
    }

    while (_keep_running && !clock.times_up()) {
        Message msg(Command::ActionType::NONE);
        while (actionQueue.try_pop(msg)) {
            uint32_t clientId = msg.id();
            std::shared_ptr<Character> character = clientCharacters[clientId];

            switch (msg.command.action) {
                case Command::ActionType::LEFT:
                    character->moveLeft();
                    break;
                case Command::ActionType::RIGHT:
                    character->moveRigth();
                    break;
                case Command::ActionType::RUNFAST:
                    character->run();
                    break;
                case Command::ActionType::JUMP:
                    character->jump();
                    break;
                case Command::ActionType::SPECIAL:
                    character->special_action();
                    break;
                case Command::ActionType::FIRE:
                    character->disparando = true;
                    break;
                case Command::ActionType::STOPLEFT:
                    character->stopMovingLeft();
                    break;
                case Command::ActionType::STOPRIGHT:
                    character->stopMovingRight();
                    break;
                case Command::ActionType::RUN:
                    character->stoprunning();
                    break;
                case Command::ActionType::STOPFIRE:
                    character->disparando = false;
                    break;
                case Command::ActionType::CHANGE_AMMO:
                    character->change_selected_ammo();
                    break;
                case Command::ActionType::QUIT: {
                    // cppcheck-suppress shadowVariable
                    Container c(1, clientId, 0, 0, 0, 0, 0, AnimationType::NONE_ANIMATION,
                                EntityType::NONE_ENTITY, 0, {EntityType::NONE_ENTITY, 0}, 0, "");
                    stateQueue.push(c);
                    entes.erase(std::remove_if(entes.begin(), entes.end(),
                                               [&](std::shared_ptr<Entity> o) {
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
            broadcaster.erase_client(client.first);
        }
    }
    gameEnded = true;
    _is_alive = false;
}

void Game::getMapName(std::string& mapName) { mapName = this->mapName; }

void Game::addPlayer(uint32_t clientId, uint32_t character, std::string name) {
    std::lock_guard<std::mutex> lock(clientCharactersMutex);

    if (character == 0) {
        std::shared_ptr<Jazz> c(new Jazz(5, 20, config, stateQueue, name));
        c->set_id(clientId);
        clientCharacters[clientId] = c;
        objetos.agregar_objeto(c);
        entes.push_back(c);
    } else if (character == 1) {
        std::shared_ptr<Lori> c(new Lori(5, 20, config, stateQueue, name));
        c->set_id(clientId);
        clientCharacters[clientId] = c;
        objetos.agregar_objeto(c);
        entes.push_back(c);
    } else {
        std::shared_ptr<Spaz> c(new Spaz(5, 20, config, stateQueue, name));
        c->set_id(clientId);
        clientCharacters[clientId] = c;
        objetos.agregar_objeto(c);
        entes.push_back(c);
    }
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
