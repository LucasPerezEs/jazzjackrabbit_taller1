#include "headers/GamesManager.h"

#include "iostream"

std::map<std::string, float> load_config_YAML(const std::string& path) {
    std::map<std::string, float> config;
    YAML::Node yaml;

    try {
        yaml = YAML::LoadFile(path);
    } catch (std::exception& e) {
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

    // Bat
    config["bat_life"] = yaml["bat"]["life"].as<float>();
    config["bat_damage"] = yaml["bat"]["damage"].as<float>();
    config["bat_speed"] = yaml["bat"]["speed"].as<float>();
    config["bat_prob_carrot"] = yaml["bat"]["prob_carrot"].as<float>();
    config["bat_prob_ammo"] = yaml["bat"]["prob_ammo"].as<float>();
    config["bat_prob_goldcoin"] = yaml["bat"]["prob_goldcoin"].as<float>();

    // Monkey
    config["monkey_life"] = yaml["monkey"]["life"].as<float>();
    config["monkey_damage"] = yaml["monkey"]["damage"].as<float>();
    config["monkey_speed"] = yaml["monkey"]["speed"].as<float>();
    config["monkey_prob_carrot"] = yaml["monkey"]["prob_carrot"].as<float>();
    config["monkey_prob_ammo"] = yaml["monkey"]["prob_ammo"].as<float>();
    config["monkey_prob_goldcoin"] = yaml["monkey"]["prob_goldcoin"].as<float>();

    // Pickups
    config["goldcoin_addscore"] = yaml["goldcoin"]["add_score"].as<float>();
    config["carrot_addlife"] = yaml["carrot"]["add_life"].as<float>();
    config["ammo_addammo"] = yaml["ammo"]["add_ammo"].as<float>();

    // Weapon
    config["weapon_firerate"] = yaml["weapon"]["fire_rate"].as<float>();
    config["weapon_initial_ammo"] = yaml["weapon"]["initial_ammo"].as<float>();

    // Bullets
    config["bullet_speed"] = yaml["bullet"]["speed"].as<float>();
    config["bullet_damage"] = yaml["bullet"]["damage"].as<float>();

    config["banana_speed"] = yaml["banana"]["speed"].as<float>();
    config["banana_damage"] = yaml["banana"]["damage"].as<float>();

    return config;
}

GamesManager::GamesManager(): setupQueue(), stateQueue() {}

bool GamesManager::createGame(std::string gameId, uint32_t maxPlayers,
                              // cppcheck-suppress passedByValue
                              std::vector<uint32_t> cheats) {
    std::lock_guard<std::mutex> lock(gamesMutex);

    std::map<std::string, float> config = load_config_YAML("../config.yml");

    activate_cheats(cheats, config);

    GameBroadcasterContainer* newGame =
            new GameBroadcasterContainer(std::move(config), maxPlayers, setupQueue);

    if (newGame != nullptr) {
        games[gameId] = newGame;
        newGame->start();
        return true;
    }
    return false;
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

    // cppcheck-suppress unreadVariable
    Message msg(Setup::ActionType::NONE);
    Container container({}, {}, {}, {}, {});
    bool ok;


    // std::map<std::string, float> config = load_config_YAML("../config.yml");
    while (_keep_running) {
        msg = setupQueue.pop();
        uint32_t clientId = msg.id();
        switch (msg.setup.action) {
            case Setup::JOIN_GAME:
                ok = joinGame(msg.setup.gameId, clients[clientId], msg.setup.character);
                container = Container(Setup::JOIN_GAME, msg.setup.gameId, msg.setup.maxPlayers,
                                      msg.setup.cheats, ok);
                clients[clientId]->pushState(container);
                break;
            case Setup::CREATE_GAME:
                ok = createGame(msg.setup.gameId, msg.setup.maxPlayers, msg.setup.cheats);
                container = Container(Setup::CREATE_GAME, msg.setup.gameId, msg.setup.maxPlayers,
                                      msg.setup.cheats, ok);
                clients[clientId]->pushState(container);
                break;
            case Setup::GET_GAME_LIST: {
                std::vector<std::string> gameList;
                ok = listGames(gameList);
                container = Container(Setup::GET_GAME_LIST, gameList, ok);
                clients[clientId]->pushState(container);
                break;
            }
            default:
                std::cout << "Comando desconocido" << std::endl;
                break;
        }
        reap_offline_games();
    }
    stop();
    _is_alive = false;
}


void GamesManager::reap_offline_games() {
    for (auto it = games.begin(); it != games.end();) {
        if (!it->second->is_running()) {
            it->second->stop();
            it->second->join();
            delete it->second;
            it = games.erase(it);
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
    }
    games.clear();
}

void GamesManager::stop() {
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
