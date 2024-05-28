#include "headers/game.h"

#include <algorithm>

Game::Game(Client& client, SdlWindow& window, Player& player, Queue<Contenedor>& queue):
        receiverQueue(queue), client(client), window(window), player(player) {}

void Game::run() {
    uint32_t time1 = 0;
    time1 = SDL_GetTicks();

    client.go_online();

    std::vector<std::vector<float>> objetos;


    while (client.is_online()) {

        while (true) {
            Contenedor c(0, 0, 0, 0, 0, 0);
            if (!receiverQueue.try_pop(c)) {
                break;
            }
            // std::cout << c.id() << "\n";
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

        SDL_RenderClear(window.getRenderer());  // renderizo todo como un rectangulo

        SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255);

        for (auto o: objetos) {
            SDL_Rect r;
            r.h = ((o[2] - o[4]) * 6);
            r.w = ((o[3] - o[1]) * 8);
            r.x = o[1] * 8;
            r.y = 600 - (o[2] * 6);
            SDL_RenderDrawRect(window.getRenderer(), &r);
        }
        SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);

        SDL_RenderPresent(window.getRenderer());

        uint32_t time2;
        time2 = SDL_GetTicks();
        uint32_t rest = FRAME_RATE - (time2 - time1);
        time1 = time2;

        usleep(rest);
    }

    this->close();
}

void Game::update(float dt) { this->player.update(dt); }

void Game::render() {
    this->window.fill();
    player.render();
    this->window.render();
}

void Game::close() { client.close(); }
