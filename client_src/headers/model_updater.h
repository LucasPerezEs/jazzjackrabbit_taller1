#ifndef MODEL_UPDATER_H
#define MODEL_UPDATER_H

#include <algorithm>
#include <exception>
#include <map>
#include <vector>

#include <SDL.h>

#include "../../common_src/headers/entity_commands.h"
#include "../../common_src/headers/queue.h"
#include "../../common_src/headers/thread.h"

#include "SdlTexture.h"
#include "SdlWindow.h"
#include "UIManager.h"
#include "entity.h"
#include "player.h"
#include "protocol.h"

#define FRAME_RATE 1000000.0f / 20.0f

class Client;

class ModelUpdater: public Thread {

private:
    ClientProtocol& protocol;
    bool was_closed;
    std::map<int, Entity*>& entidades;
    std::map<int, std::map<int, Animation*>> animations;
    Queue<Contenedor>& reciever_queue;
    Client* cliente;
    std::map<int, Player*>& personajes;
    UIManager& ui_manager;

    void init_animations(SdlWindow& window);

    void update_entity(Contenedor& c);

    void update_player(Contenedor& c);

    void despawn_entity(Contenedor& c);

public:
    ModelUpdater(ClientProtocol& protocol, SdlWindow& window, std::map<int, Entity*>& entidades,
                 Queue<Contenedor>& reciever_queue, std::map<int, Player*>& personajes,
                 UIManager& ui_manager);

    virtual void run() override;


    void update(float dt);

    void close();

    bool is_running();

    void agregar_cliente(Client* c);

    ModelUpdater(const ModelUpdater&) = delete;
    ModelUpdater& operator=(const ModelUpdater&) = delete;

    ModelUpdater(ModelUpdater&&) = default;
    ModelUpdater& operator=(ModelUpdater&&) = default;
};

#endif
