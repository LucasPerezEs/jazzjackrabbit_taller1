#include "headers/model_updater.h"

ModelUpdater::ModelUpdater(ClientProtocol& protocol, SdlWindow& window, Player& player):
        protocol(protocol), was_closed(false), window(window), player(player) {
    this->init_textures();
}

void ModelUpdater::init_textures() {
    // this->textures[JAZZ][IDLE] = new SdlTexture("../client_src/assets/jazz_idle.png",
    // this->window, Color{0x2C, 0x66, 0x96}); this->textures[JAZZ][WALK] = new
    // SdlTexture("../client_src/assets/jazz_idle.png", this->window, Color{0x2C, 0x66, 0x96});
    // this->textures[JAZZ][RUN] = new SdlTexture("../client_src/assets/jazz_idle.png",
    // this->window, Color{0x2C, 0x66, 0x96}); this->textures[JAZZ][JUMP] = new
    // SdlTexture("../client_src/assets/jazz_idle.png", this->window, Color{0x2C, 0x66, 0x96});
    // this->textures[JAZZ][FALL] = new SdlTexture("../client_src/assets/jazz_idle.png",
    // this->window, Color{0x2C, 0x66, 0x96}); this->textures[JAZZ][RECIEVE_DAMAGE] = new
    // SdlTexture("../client_src/assets/jazz_idle.png", this->window, Color{0x2C, 0x66, 0x96});
    // this->textures[JAZZ][DEAD] = new SdlTexture("../client_src/assets/jazz_idle.png",
    // this->window, Color{0x2C, 0x66, 0x96}); this->textures[JAZZ][SPECIAL_ACTION] = new
    // SdlTexture("../client_src/assets/jazz_idle.png", this->window, Color{0x2C, 0x66, 0x96});

    // this->textures[LORI][IDLE] = new SdlTexture("../client_src/assets/jazz_idle.png",
    // this->window, Color{0x2C, 0x66, 0x96});
    //  etc...

    this->textures[0][0] = new SdlTexture("../client_src/assets/jazz_walking.png", this->window,
                                          Color{0x2C, 0x66, 0x96});
    this->textures[0][1] = new SdlTexture("../client_src/assets/jazz_intoxicated_walking.png",
                                          this->window, Color{0x2C, 0x66, 0x96});
}

void ModelUpdater::run() {
    while (this->is_running()) {
        this->update(FRAME_RATE);
    }
}

void ModelUpdater::update(float dt) {

    try {

        std::pair<State::StateType, SpecialAction::SpecialActionType> update =
                protocol.receive_update();

        State::StateType stateType = update.first;
        SpecialAction::SpecialActionType actionType = update.second;

        if (stateType != State::NONE) {
            switch (stateType) {
                case State::INTOXICATED:
                    std::cout << "INTOXICATED" << std::endl;
                    this->player.change_animation(
                            this->textures[0][1],
                            12);  // No me gusta que el n_frames este hardcodeado
                    break;
                case State::DEATH:
                    std::cout << "DEATH" << std::endl;
                    break;
                default:
                    std::cerr << "Estado no reconocido: " << std::endl;
                    break;
            }
        }

        if (actionType != SpecialAction::NONE) {
            switch (actionType) {
                case SpecialAction::PUNCH:
                    std::cout << "PUNCH" << std::endl;
                    break;
                case SpecialAction::SHORTKICK:
                    std::cout << "SHORTKICK" << std::endl;
                    break;
                case SpecialAction::SIDEKICK:
                    std::cout << "SIDEKICK" << std::endl;
                    break;
                default:
                    std::cerr << "Special Action no reconocida: " << std::endl;
                    break;
            }
        }


    } catch (const std::exception& e) {
        std::cerr << "Protocolo cerrado" << e.what() << "\n";
        this->close();
    }
}

bool ModelUpdater::is_running() { return not was_closed; }

void ModelUpdater::close() { this->was_closed = true; }
