#include "headers/GamesManager.h"

#include "iostream"

std::map<std::string, float> load_config_YAML(const std::string& path) {
    std::map<std::string, float> config;
    YAML::Node yaml;

    try {
        yaml = YAML::LoadFile(path);
    } catch (std::exception& e) {
        std::cout << "entro en catch C\n";
        std::cerr << e.what() << std::endl;
    }

    // Game
    config["game_time"] = yaml["game_time"].as<float>();
    config["gravity"] = yaml["gravity"].as<float>();

    // Player
    config["player_life"] = yaml["player"]["life"].as<float>();
    config["player_special_attack_dmg"] = yaml["player"]["special_attack_dmg"].as<float>();
    config["player_speed"] = yaml["player"]["speed"].as<float>();
    config["player_run_speed"] = yaml["player"]["run_speed"].as<float>();
    config["player_jump"] = yaml["player"]["jump"].as<float>();

    // Ghost
    config["ghost_life"] = yaml["ghost"]["life"].as<float>();
    config["ghost_damage"] = yaml["ghost"]["damage"].as<float>();
    config["ghost_speed"] = yaml["ghost"]["speed"].as<float>();
    config["ghost_prob_carrot"] = yaml["ghost"]["prob_carrot"].as<float>();
    config["ghost_prob_ammo"] = yaml["ghost"]["prob_ammo"].as<float>();
    config["ghost_prob_goldcoin"] = yaml["ghost"]["prob_goldcoin"].as<float>();
    config["ghost_prob_rocket"] = yaml["ghost"]["prob_rocket"].as<float>();

    // Bat
    config["bat_life"] = yaml["bat"]["life"].as<float>();
    config["bat_damage"] = yaml["bat"]["damage"].as<float>();
    config["bat_speed"] = yaml["bat"]["speed"].as<float>();
    config["bat_prob_carrot"] = yaml["bat"]["prob_carrot"].as<float>();
    config["bat_prob_ammo"] = yaml["bat"]["prob_ammo"].as<float>();
    config["bat_prob_goldcoin"] = yaml["bat"]["prob_goldcoin"].as<float>();
    config["bat_prob_rocket"] = yaml["bat"]["prob_rocket"].as<float>();

    // Monkey
    config["monkey_life"] = yaml["monkey"]["life"].as<float>();
    config["monkey_damage"] = yaml["monkey"]["damage"].as<float>();
    config["monkey_speed"] = yaml["monkey"]["speed"].as<float>();
    config["monkey_prob_carrot"] = yaml["monkey"]["prob_carrot"].as<float>();
    config["monkey_prob_ammo"] = yaml["monkey"]["prob_ammo"].as<float>();
    config["monkey_prob_goldcoin"] = yaml["monkey"]["prob_goldcoin"].as<float>();
    config["monkey_prob_rocket"] = yaml["monkey"]["prob_rocket"].as<float>();

    // Pickups
    config["goldcoin_addscore"] = yaml["goldcoin"]["add_score"].as<float>();
    config["carrot_addlife"] = yaml["carrot"]["add_life"].as<float>();
    config["ammo_addammo"] = yaml["ammo"]["add_ammo"].as<float>();
    config["rocket_pickup_addammo"] = yaml["rocket_pickup"]["add_ammo"].as<float>();


    // Bullets
    config["bullet_speed"] = yaml["bullet"]["speed"].as<float>();
    config["bullet_damage"] = yaml["bullet"]["damage"].as<float>();
    config["bullet_firerate"] = yaml["bullet"]["fire_rate"].as<float>();
    config["bullet_initial_ammo"] = yaml["bullet"]["initial_ammo"].as<float>();

    config["rocket_speed"] = yaml["rocket"]["speed"].as<float>();
    config["rocket_damage"] = yaml["rocket"]["damage"].as<float>();
    config["rocket_firerate"] = yaml["rocket"]["fire_rate"].as<float>();
    config["rocket_initial_ammo"] = yaml["rocket"]["initial_ammo"].as<float>();

    config["banana_speed"] = yaml["banana"]["speed"].as<float>();
    config["banana_damage"] = yaml["banana"]["damage"].as<float>();

    return config;
}

GamesManager::GamesManager(): setupQueue(), stateQueue() {}

bool GamesManager::createGame(std::string gameId, uint32_t maxPlayers,
                              // cppcheck-suppress passedByValue
                              std::vector<uint32_t> cheats) {
    std::lock_guard<std::mutex> lock(gamesMutex);

    if (games.count(gameId) == 0) {
        std::map<std::string, float> config = load_config_YAML("../config.yml");

        activate_cheats(cheats, config);

        GameBroadcasterContainer* newGame =
                new GameBroadcasterContainer(std::move(config), maxPlayers, setupQueue);

        if (newGame != nullptr) {
            games[gameId] = newGame;
            // newGame->start();
            return true;
        }
    }

    return false;
}

// cppcheck-suppress constParameter
bool GamesManager::createMap(std::string& mapName,
                             std::vector<std::vector<std::string>>& mapReceived) {

    std::string path;
    path = "../server_src/maps/" + mapName;

    std::ifstream archivo(path);
    if (!archivo.is_open()) {
        std::cout << "El archivo no existe." << std::endl;
        return false;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::vector<std::string> fila;
        size_t pos = 0;
        while ((pos = linea.find(',')) != std::string::npos) {
            fila.push_back(linea.substr(0, pos));
            linea.erase(0, pos + 1);
        }
        fila.push_back(linea);
        mapReceived.push_back(fila);
    }

    archivo.close();
    return true;
}

bool GamesManager::savedMap(std::string& mapName,
                            // cppcheck-suppress constParameter
                            std::vector<std::vector<std::string>>& mapReceived) {

    /*
        std::ofstream outputFile(mapName);

        if (!outputFile.is_open()) {
            std::cerr << "Error al abrir el archivo: " << mapName << std::endl;
            return false;
        }

        for (const auto& row : mapReceived) {
            for (const auto& element : row) {
                outputFile << element << ",";
            }
            outputFile << std::endl;
        }

        outputFile.close();
    */
    int fila = 0;

    for (const auto& row: mapReceived) {
        std::cout << fila << std::endl;
        for (const auto& column: row) {
            std::cout << column << ",";
        }
        fila++;
        std::cout << "\n";
    }
    return true;
}

bool GamesManager::joinGame(const std::string& gameId, ClientHandler* client, uint32_t character) {
    std::lock_guard<std::mutex> lock(gamesMutex);

    auto it = games.find(gameId);
    if (it != games.end() && it->second->canAddPlayer()) {
        it->second->addPlayer(client, character);
        return true;
    }

    return false;
}

bool GamesManager::listGames(std::vector<std::string>& gameList) {
    std::lock_guard<std::mutex> lock(gamesMutex);

    for (const auto& game: games) {
        std::stringstream stm;
        stm << game.first << " " << game.second->number_of_players() << "/"
            << game.second->max_players() << "\n";
        gameList.push_back(stm.str());
    }

    if (gameList.size() > 0) {
        return true;
    }

    return false;
}

bool GamesManager::setName(std::string& clientName, uint32_t id) {
    for (auto client: clients) {
        if (client.second->getName().compare(clientName) == 0) {
            return false;
        }
    }
    clients[id]->setName(clientName);
    return true;
}


void GamesManager::activate_cheats(const std::vector<uint32_t>& cheats,
                                   std::map<std::string, float>& config) {
    if (cheats.size() == 0) {
        return;
    }

    for (uint32_t i = 0; i < cheats.size(); i++) {
        switch (cheats[i]) {
            case INMORTAL:
                std::cout << "Cheat inmortal activado" << std::endl;
                config["player_life"] = 10000;
                break;

            case ONE_SHOT_ONE_KILL:
                std::cout << "Cheat one shot one kill activado" << std::endl;
                config["ghost_life"] = 1;
                config["monkey_life"] = 1;
                config["bat_life"] = 1;
                break;

            case MOON_GRAVITY:
                std::cout << "Cheat moon gravity activado" << std::endl;
                config["gravity"] = 0.05;
                break;

            case HARD_ENEMIES:
                std::cout << "Cheat hard enemies activado" << std::endl;
                config["ghost_damage"] = 50;
                config["bat_damage"] = 50;
                config["monkey_damage"] = 50;
                break;

            case EXTRA_TIME:
                std::cout << "Cheat extra time activado" << std::endl;
                config["game_time"] = 500;
                break;

            default:
                break;
        }
    }
}

void GamesManager::run() {

    Message msg(Setup::ActionType::NONE);
    // Container container({}, {}, {}, {}, {});
    bool ok;


    // std::map<std::string, float> config = load_config_YAML("../config.yml");

    while (_keep_running) {
        try {
            msg = setupQueue.pop();
        } catch (ClosedQueue& q) {
            break;
        } catch (...) {
            break;
        }

        uint32_t clientId = msg.id();
        switch (msg.setup.action) {
            case Setup::JOIN_GAME: {
                ok = joinGame(msg.setup.gameId, clients[clientId], msg.setup.character);
                Container container = Container(Setup::JOIN_GAME, msg.setup.gameId,
                                                msg.setup.maxPlayers, msg.setup.cheats, ok);
                clients[clientId]->pushState(container);
                break;
            }
            case Setup::CREATE_GAME: {
                ok = createGame(msg.setup.gameId, msg.setup.maxPlayers, msg.setup.cheats);
                std::cout << "Creando game\n";
                Container container = Container(Setup::CREATE_GAME, msg.setup.gameId,
                                                msg.setup.maxPlayers, msg.setup.cheats, ok);
                clients[clientId]->pushState(container);
                std::cout << "Pusheando cola de create a client\n";
                break;
            }
            case Setup::GET_GAME_LIST: {
                std::vector<std::string> gameList;
                ok = listGames(gameList);
                Container container = Container(Setup::GET_GAME_LIST, gameList, ok);
                clients[clientId]->pushState(container);
                break;
            }
            case Setup::CREATE_MAP: {
                std::vector<std::vector<std::string>> mapReceived;
                ok = createMap(msg.setup.mapName, mapReceived);
                Container container = Container(Setup::CREATE_MAP, mapReceived, ok);
                clients[clientId]->pushState(container);
                break;
            }
            case Setup::SAVE_MAP: {
                ok = savedMap(msg.setup.mapName, msg.setup.map);
                Container container = Container(Setup::SAVE_MAP, ok);
                clients[clientId]->pushState(container);
                break;
            }
            case Setup::SET_NAME: {
                ok = setName(msg.setup.mapName, clientId);
                Container container = Container(Setup::SET_NAME, ok);
                clients[clientId]->pushState(container);
                break;
            }
            default:
                std::cout << "Comando desconocido" << std::endl;
                break;
        }
        reap_offline_games();
    }

    // stop();
    _is_alive = false;
}


void GamesManager::reap_offline_games() {
    for (auto it = games.begin(); it != games.end();) {
        if (!it->second->is_running()) {
            it->second->stop();
            it->second->join();
            delete it->second;
            it = games.erase(it);
            std::cout << "Borrando game\n";
        } else {
            ++it;
        }
    }
}

void GamesManager::kill_all_games() {
    for (auto& gamePair: games) {
        gamePair.second->stop();
        gamePair.second->join();
        delete gamePair.second;
        std::cout << "borrando game\n";
    }
    games.clear();
}

void GamesManager::stop() {
    setupQueue.close();
    _keep_running = false;
    kill_all_games();
}


GamesManager::~GamesManager() {
    std::lock_guard<std::mutex> lock(gamesMutex);
    for (auto& gamePair: games) {
        delete gamePair.second;
    }
    games.clear();
}

void GamesManager::addClient(uint32_t clientId, ClientHandler* client) {
    std::lock_guard<std::mutex> lock(gamesMutex);

    clients[clientId] = client;
    client->setReceiverQueue(&setupQueue);
}
