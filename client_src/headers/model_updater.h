#ifndef MODEL_UPDATER_H
#define MODEL_UPDATER_H

#include <exception>
#include <map>

#include <SDL.h>

#include "../../common_src/headers/commands.h"
#include "../../common_src/headers/thread.h"

#include "SdlTexture.h"
#include "SdlWindow.h"
#include "player.h"
#include "protocol.h"
#include "texture_ids.h"

#define FRAME_RATE 1000000.0f / 40.0f


class ModelUpdater: public Thread {

private:
    ClientProtocol& protocol;
    bool was_closed;
    SdlWindow& window;
    std::map<int, std::map<int, SdlTexture*>> textures;
    Player& player;  // En realidad aca tendria todas las entidades del juego.

    void init_textures();

public:
    explicit ModelUpdater(ClientProtocol& protocol, SdlWindow& window, Player& player);

    virtual void run() override;

    void update(float dt);

    void close();

    bool is_running();

    ModelUpdater(const ModelUpdater&) = delete;
    ModelUpdater& operator=(const ModelUpdater&) = delete;

    ModelUpdater(ModelUpdater&&) = default;
    ModelUpdater& operator=(ModelUpdater&&) = default;
};

#endif
