#ifndef MODEL_UPDATER_H
#define MODEL_UPDATER_H

#include <exception>

#include <SDL.h>

#include "../../common_src/headers/commands.h"
#include "../../common_src/headers/thread.h"

#include "protocol.h"

#define FRAME_RATE 1000000.0f / 40.0f


class ModelUpdater: public Thread {

private:
    ClientProtocol& protocol;
    bool was_closed;

public:
    explicit ModelUpdater(ClientProtocol& protocol);

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
