#include "headers/model_updater.h"

ModelUpdater::ModelUpdater(ClientProtocol& protocol, SdlWindow& window,
                           std::vector<std::vector<float>>& objetos,
                           Queue<Contenedor>& reciever_queue):
        protocol(protocol), was_closed(false), objetos(objetos), reciever_queue(reciever_queue) {
    this->init_textures(window);
}

void ModelUpdater::init_textures(SdlWindow& window) {
    /*this->texture[EntityType::JAZZ][AnimationType::IDLE] = new SdlTexture(PATH, window,
    Color{0x2C, 0x66, 0x96}); this->texture[EntityType::JAZZ][AnimationType::WALK] = new
    SdlTexture(PATH, window, Color{0x2C, 0x66, 0x96});
    this->texture[EntityType::JAZZ][AnimationType::RUN] = new SdlTexture(PATH, window, Color{0x2C,
    0x66, 0x96}); this->texture[EntityType::JAZZ][AnimationType::JUMP] = new SdlTexture(PATH,
    window, Color{0x2C, 0x66, 0x96});*/

    this->textures[0][0] = new SdlTexture("../client_src/assets/jazz_walking.png", window,
                                          Color{0x2C, 0x66, 0x96});
    this->textures[0][1] = new SdlTexture("../client_src/assets/jazz_intoxicated_walking.png",
                                          window, Color{0x2C, 0x66, 0x96});
}

void ModelUpdater::run() {
    while (this->is_running()) {
        this->update(FRAME_RATE);
    }
}

void ModelUpdater::update(float dt) {

    try {
        while (true) {

            Contenedor c(0, 0, 0, 0, 0, 0);
            if (!reciever_queue.try_pop(c)) {
                break;
            }

            for (long unsigned int i = 0; i <= objetos.size(); i++) {
                if (i != objetos.size() && (objetos[i])[0] == c.id()) {
                    (objetos[i])[1] = c.posx();
                    (objetos[i])[2] = c.posy();
                    (objetos[i])[3] = c.width();
                    (objetos[i])[4] = c.height();
                    (objetos[i])[5] = (float)c.borrar();
                    break;
                } else if (i == objetos.size()) {
                    std::vector<float> vector;
                    vector.push_back(c.id());
                    vector.push_back(c.posx());
                    vector.push_back(c.posy());
                    vector.push_back(c.width());
                    vector.push_back(c.height());
                    vector.push_back((float)c.borrar());
                    objetos.push_back(vector);
                    break;
                }
            }
        }

        objetos.erase(std::remove_if(objetos.begin(), objetos.end(),
                                     [](std::vector<float> o) { return o[5] == 1 ? true : false; }),
                      objetos.end());
        /*std::pair<State::StateType, SpecialAction::SpecialActionType> update =
                protocol.receive_update();

        State::StateType stateType = update.first;
        SpecialAction::SpecialActionType actionType = update.second;

        if (stateType != State::NONE) {
            switch (stateType) {
                case State::INTOXICATED:
                    std::cout << "INTOXICATED" << std::endl;
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
        }*/


    } catch (const std::exception& e) {
        std::cerr << "Protocolo cerrado" << e.what() << "\n";
        this->close();
    }
}

bool ModelUpdater::is_running() { return not was_closed; }

void ModelUpdater::close() { this->was_closed = true; }
