#include "headers/model_updater.h"

ModelUpdater::ModelUpdater(ClientProtocol& protocol): protocol(protocol), was_closed(false) {}


void ModelUpdater::run() {
    while (this->is_running()) {
        this->update(FRAME_RATE);
    }
}

void ModelUpdater::update(float dt) {
    try {
        unsigned char c;
        c = this->protocol.receiveUChar();
        std::cout << c << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Protocolo cerrado" << e.what() << "\n";
        this->close();
    }
}

bool ModelUpdater::is_running() { return not was_closed; }

void ModelUpdater::close() { this->was_closed = true; }
