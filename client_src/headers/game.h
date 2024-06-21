#ifndef GAME_H
#define GAME_H

#include <cmath>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include <unistd.h>

#include "Fuente.h"
#include "Music.h"
#include "SdlWindow.h"
#include "UIManager.h"
#include "camara.h"
#include "client.h"
#include "entity.h"
#include "event_handler.h"
#include "model_updater.h"
#include "map_creator.h"
#include "drawer.h"
#include "protocol.h"

class Game {
private:
    Queue<Container> receiverQueue;
    Client& client;
    SdlWindow window;
    std::map<int, Entity*> entidades;
    std::map<int, Player*> personajes;

    SDL_Texture* tilesetTexture;
    std::vector<std::vector<int>> tilemap;
    UIManager ui_manager;

    ClientReceiver client_receiver;
    bool gameStarted;
    bool in_menu;
    SoundManager sound_manager;
    EventHandler event_handler;  // eventos teclado (sender)
    ModelUpdater updater;        // actualizar modelos (receiver)

    void draw(const std::vector<std::vector<int>>& tilemap, SDL_Texture* tilesetTexture);

    Camara* camara;


public:
    explicit Game(Client& client);

    void run();

    void init();
    void update();
    void render();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&) = default;
    Game& operator=(Game&&) = default;

    ~Game();
};

#endif
