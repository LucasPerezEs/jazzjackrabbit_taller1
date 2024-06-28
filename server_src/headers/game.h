#ifndef SERVER_GAME_H
#define SERVER_GAME_H
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../common_src/headers/Container.h"
#include "../../common_src/headers/Message.h"
#include "../../common_src/headers/commands.h"
#include "../../common_src/headers/queue.h"
#include "../../common_src/headers/thread.h"

#include "bat.h"
#include "character.h"
#include "clock.h"
#include "ghost.h"
#include "jazz.h"
#include "lori.h"
#include "monkey.h"
#include "object_list.h"
#include "spaz.h"

class Broadcaster;

class Game: public Thread {
public:
    explicit Game(Queue<Message>& actionQueue, Queue<Container>& eventQueue, uint32_t maxPlayers,
                  const std::string& mapName, std::map<std::string, float> config,
                  Broadcaster& broadcaster, bool& gameStarted, bool& gameEnded);


    void run() override;
    void stop() override;

    void addPlayer(uint32_t clientId, uint32_t character, std::string name);

    void getMapName(std::string& mapName);

    void send_score();

    bool is_running() { return _is_alive; }

    ~Game();

private:
    Map* m;
    uint32_t maxPlayers;
    const std::string mapName;
    std::map<uint32_t, std::shared_ptr<Character>> clientCharacters;
    ObjectList objetos;
    std::vector<std::shared_ptr<Entity>> entes;

    Queue<Message>& actionQueue;
    Queue<Container>& stateQueue;

    std::map<std::string, float> config;

    Broadcaster& broadcaster;

    std::mutex clientCharactersMutex;
    Clock clock;
    bool& gameStarted;
    bool& gameEnded;
};

#endif  // SERVER_GAME_H
