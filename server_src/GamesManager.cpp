#include "headers/GamesManager.h"

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

std::string GamesManager::createGame(std::string gameId, std::map<std::string, float>& config) {
    std::lock_guard<std::mutex> lock(gamesMutex);

    GameContainer* newGame = new GameContainer(config);
    games[gameId] = newGame;

    newGame->start();

    return gameId;
}

bool GamesManager::joinGame(const std::string& gameId, ClientHandler* client) {
    std::lock_guard<std::mutex> lock(gamesMutex);
    auto it = games.find(gameId);
    if (it != games.end()) {
        it->second->addPlayer(client);
        return true;
    }
    return false;
}

std::vector<std::string> GamesManager::listGames() {
    std::lock_guard<std::mutex> lock(gamesMutex);
    std::vector<std::string> gameList;
    for (const auto& game: games) {
        std::cout << game.first << std::endl;
        gameList.push_back(game.first);
    }
    return gameList;
}


void GamesManager::run() {

    Message msg(Setup::ActionType::NONE);
    std::map<std::string, float> config = load_config_YAML("../config.yml");
    while (_keep_running) {
        msg = setupQueue.pop();
        uint32_t clientId = msg.id();
        switch (msg.setup.action) {
            case Setup::JOIN_GAME:
                joinGame(msg.setup.gameId, clients[clientId]);
                //push join
                break;
            case Setup::CREATE_GAME:
                createGame(msg.setup.gameId, config);
                // push create
                break;
            case Setup::GET_GAME_LIST:
                listGames();
                //push gamelist
                break;
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