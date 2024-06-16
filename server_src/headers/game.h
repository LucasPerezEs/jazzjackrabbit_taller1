//
//#ifndef GAME_H
//#define GAME_H
//
//#include <string>
//
//#include "aceptador.h"
//#include "partida.h"
//
// class Game {
// private:
//    const std::string& servname;
//
// public:
//    explicit Game(const std::string& servname);
//
//    void init_game();
//
//    Game(const Game&) = delete;
//    Game& operator=(const Game&) = delete;
//};
//
//#endif

#ifndef SERVER_GAME_H
#define SERVER_GAME_H
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../common_src/headers/commands.h"
#include "../../common_src/headers/queue.h"
#include "../../common_src/headers/thread.h"
#include "../../common_src/headers/Message.h"
#include "../../common_src/headers/Container.h"
#include "bat.h"
#include "clock.h"
#include "ghost.h"
#include "jazz.h"
#include "lista_objetos.h"
#include "lori.h"
#include "monkey.h"
#include "personaje.h"
#include "spaz.h"

class Game: public Thread {
public:
    explicit Game(Queue<Message>& actionQueue, Queue<Container>& eventQueue, uint32_t maxPlayers,
                  std::map<std::string, float>& config);

    void run() override;
    void stop() override;

    void addPlayer(uint32_t clientId);

    bool is_running() { return _is_alive; }

private:
    uint32_t maxPlayers;
    std::unordered_map<uint32_t, Personaje*> clientCharacters;
    ListaObjetos objetos;
    std::vector<Ente*> entes;

    Queue<Message>& actionQueue;
    Queue<Container>& stateQueue;

    std::map<std::string, float>& config;

    std::mutex clientCharactersMutex;
    Clock clock;
    bool gameStarted;
};

#endif  // SERVER_GAME_H
