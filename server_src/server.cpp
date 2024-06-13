#include "headers/server.h"

Server::Server(const char* servname): srv(servname) {}

std::map<std::string, float> Server::load_config(const std::string& path) {
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

    // Enemy
    config["ghost_life"] = yaml["ghost"]["life"].as<float>();
    config["ghost_damage"] = yaml["ghost"]["damage"].as<float>();
    config["ghost_speed"] = yaml["ghost"]["speed"].as<float>();
    config["ghost_prob_carrot"] = yaml["ghost"]["prob_carrot"].as<float>();
    config["ghost_prob_ammo"] = yaml["ghost"]["prob_ammo"].as<float>();
    config["ghost_prob_goldcoin"] = yaml["ghost"]["prob_goldcoin"].as<float>();

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

    return config;
}

void Server::run() {

    int c;

    Queue<Command> actionQueue;
    Queue<Contenedor> stateQueue;

    std::list<ClientHandler*> clients;

    std::map<std::string, float> config = this->load_config("../config.yml");


    Game game(actionQueue, stateQueue, config);
    Acceptor thread_acceptador(srv, clients, actionQueue, game);
    Broadcaster br(clients, stateQueue);


    game.start();
    thread_acceptador.start();
    br.start();


    do {
        c = getchar();
    } while (c != 'q');

    thread_acceptador.stop();

    game.stop();
    br.stop();

    thread_acceptador.join();
    game.join();
    br.join();
}
