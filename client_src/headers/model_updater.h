#ifndef MODEL_UPDATER_H
#define MODEL_UPDATER_H

#include <algorithm>
#include <exception>
#include <map>
#include <vector>

#include <SDL.h>

#include "../../common_src/headers/queue.h"
#include "../../common_src/headers/thread.h"

#include "SdlTexture.h"
#include "SdlWindow.h"
#include "protocol.h"
#include "texture_ids.h"

#define FRAME_RATE 1000000.0f / 60.0f


class ModelUpdater: public Thread {

private:
    ClientProtocol& protocol;
    bool was_closed;
    std::vector<std::vector<float>>& objetos;
    std::map<int, std::map<int, SdlTexture*>> textures;
    Queue<Contenedor>& reciever_queue;

    void init_textures(SdlWindow& window);

public:
    ModelUpdater(ClientProtocol& protocol, SdlWindow& window,
                 std::vector<std::vector<float>>& objetos, Queue<Contenedor>& reciever_queue);

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
