#include "objeto.h"
#include "personaje.h"
#include "enemigo.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <map>


void leer_entrada_estandar(bool &aux, Personaje& p, std::map<Objeto*, Objeto*>& objetos) {
    std::string line;
    while (true) {
        std::getline(std::cin, line);
        if (line == "a") {
            p.mover(-1, 0);
        }
        else if (line == "d") {
            p.mover(1, 0);
        }
        else if (line == "q") {
            aux = false;
            break;
        }
        else if (line == "s") {
            p.disparar(objetos);
        }
    }
}

int main() {
    std::map<Objeto*, Objeto*> objetos;
    Personaje p1 = Personaje(0, 0, 2, 2, 100);
    Personaje p2 = Personaje(4, 0, 2, 2, 100);
    Enemigo e = Enemigo(9, 0, 2, 2, 100);
    Enemigo e2 = Enemigo(13, 0, 2, 2, 100);
    objetos[&p1] = &p1;
    objetos[&p2] = &p2;
    objetos[&e] = &e;
    objetos[&e2] = &e2;
    
    bool run = true;
    std::thread t = std::thread(&leer_entrada_estandar, std::ref(run), std::ref(p1), std::ref(objetos));
    while (run) {
        for (auto it = objetos.cbegin(); it != objetos.cend(); )
        {
            if (it->second->borrar)
            {
                objetos.erase(it++);
            }
            else
            {
                for (auto a: objetos) {
                    it->second->colision(*a.second);
                }
                ++it;
            }
        }
        for (auto o: objetos) {
            o.second->avanzar();
        } 
        std::cout << "vida del enemigo " << e.vida << "\n";
        std::cout << "vida del enemigo 2 " << e2.vida << "\n";
        //std::cout << "p1 x: (" << p1.x << "," << p1.width << ")\n";
        //std::cout << "p2 x: (" << p2.x << "," << p2.width << ")\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    t.join();
}
