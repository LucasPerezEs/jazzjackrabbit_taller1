#include "../headers/mapa.h"
#include <cstdlib>
#include "../headers/monkey.h"
#include "../headers/ghost.h"
#include "../headers/bat.h"
#include "../headers/bat.h"
#include "../headers/gem.h"
#include "../headers/gold_coin.h"

Piso::Piso(float posx, float posy, float width,
           float height) {  // Lo llame piso pero tambien puede ser una pared
    x = posx;
    y = posy;  // hitbox
    w = width;
    h = height;
}

bool Piso::colision(float posx, float posy, float width, float height) {
    if (x < (posx + width) && (x + w) > posx && y < (posy + height) && (y + h) > posy) {
        return true;
    }
    return false;
}


DiagonalIzquierda::DiagonalIzquierda(float posx, float posy, float width, float height) {
    x = posx;
    y = posy;  // hitbox
    w = width;
    h = height;
}

bool DiagonalIzquierda::colision(float posx, float posy, float width, float height) {
    if (x < (posx + width) && (x + w) > posx && y < (posy + height) && (y + h) > posy) {
        return true;
    }
    return false;
}


DiagonalDerecha::DiagonalDerecha(float posx, float posy, float width, float height) {
    x = posx;
    y = posy;  // hitbox
    w = width;
    h = height;
}

bool DiagonalDerecha::colision(float posx, float posy, float width, float height) {
    if (x < (posx + width) && (x + w) > posx && y < (posy + height) && (y + h) > posy) {
        return true;
    }
    return false;
}

std::vector<std::vector<int>> Mapa::cargarCSV(const std::string& ruta) {
    std::vector<std::vector<int>> matriz;
    std::ifstream archivo(ruta);

    if (archivo.is_open()) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            std::vector<int> fila;
            std::stringstream ss(linea);
            std::string valor;
            while (std::getline(ss, valor, ',')) {
                fila.push_back(std::stoi(valor));
            }
            matriz.push_back(fila);
        }
        archivo.close();
    } else {
        std::cout << "No se pudo abrir el archivo en server" << std::endl;
    }

    return matriz;
}

Mapa::Mapa(const std::string& mapName) {

    std::string path = "../server_src/maps/" + mapName;
    std::vector<std::vector<int>> tilemap = cargarCSV(path);

    std::string spawn_path = "../server_src/maps/" + mapName + "_spawns";
    spawns = cargarCSV(spawn_path);
    for (auto spawn: spawns) {
        if (spawn[0] == 0) {
            spawnsPersonaje.emplace_back(spawn);
        }
        else {
            spawnsOtros.emplace_back(spawn);
        }
    }


    for (std::vector<int>::size_type i = 0; i < tilemap.size(); i++) {
        for (std::vector<int>::size_type j = 0; j < tilemap[i].size(); j++) {
            if (tilemap[i][j] != -1) {

                if (tilemap[i][j] == 18 || tilemap[i][j] == 29 || tilemap[i][j] == 47 || tilemap[i][j] == 58) {
                    DiagonalIzquierda* diagonal =
                            new DiagonalIzquierda(j, (tilemap.size() - 1 - i), 1, 1);
                    std::cout << "hay diagonal en " << j << ", " << (tilemap.size() - 1 - i) << "\n";
                    diagonalesIzq.push_back(diagonal);
                } else if (tilemap[i][j] == 13 || tilemap[i][j] == 22 || tilemap[i][j] == 44 || tilemap[i][j] == 53) {
                    DiagonalDerecha* diagonal =
                            new DiagonalDerecha(j, (tilemap.size() - 1 - i), 1, 1);
                    std::cout << "hay diagonal en " << j << ", " << (tilemap.size() - 1 - i) << "\n";
                    diagonalesDer.push_back(diagonal);
                } else if ((tilemap[i][j] < 70 && tilemap[i][j] > 0)) {
                    Piso* piso =
                            new Piso(j, (tilemap.size() - 1 - i), 1,
                                     1);  // cada numero en la matriz representa un espacio de 1x1
                    objetos.push_back(piso);
                    // std::cout << "Entro al creador de piso con fila" << i << " y columna: " << j
                    // << std::endl;
                }
            }
        }
    }
}

bool Mapa::CheckColision(
        float x, float y, float w,
        float h) {  // devuelve true si la hitbox que le paso por parametro colisiona con el mapa
    for (auto p: objetos) {
        if (p->colision(x, y, w, h)) {
            return true;
        }
    }
    for (auto d: diagonalesIzq) {
        if (d->colision(x, y, w, h)) {
            return true;
        }
    }
    for (auto d: diagonalesDer) {
        if (d->colision(x, y, w, h)) {
            return true;
        }
    }
    return false;
}

std::vector<int> Mapa::get_spawn(int type) {
    std::vector<int> res;
    if (type == 0 && spawnsPersonaje.size() > 0) {

        int i = rand()%spawnsPersonaje.size();
        res.emplace_back(spawnsPersonaje[i][1]);
        res.emplace_back(spawnsPersonaje[i][2]);
        return res;
    }

    res.emplace_back(-1);
    res.emplace_back(-1);
    return res;
}

void Mapa::spawn(ListaObjetos& objetos, std::vector<std::shared_ptr<Ente>>& entes, std::map<std::string, float> &config, Queue<Container>& q) {
    for (auto objeto: spawnsOtros) {
        //std::cout << "posicion es " << objeto[1] << ", " << objeto[2] << "\n";
        if (objeto[0] == 1) {
            std::shared_ptr<Monkey> m (new Monkey(objeto[1], objeto[2], config));
            objetos.agregar_objeto(m);
            entes.emplace_back(m);
        }
        else if (objeto[0] == 2) {
            std::shared_ptr<Ghost> g (new Ghost(objeto[1], objeto[2], config));
            objetos.agregar_objeto(g);
            entes.emplace_back(g);
        }
        else if (objeto[0] == 3) {
            std::shared_ptr<Bat> b (new Bat(objeto[1], objeto[2], config));
            objetos.agregar_objeto(b);
            entes.emplace_back(b);
        }
        else if (objeto[0] == 4) {
            std::shared_ptr<Gem> b (new Gem(objeto[1], objeto[2], config, q));
            objetos.agregar_objeto(b);
        }
        else if (objeto[0] == 5) {
            std::shared_ptr<Gold_Coin> b (new Gold_Coin(objeto[1], objeto[2], config, q));
            objetos.agregar_objeto(b);
        }
    }
}

Mapa::~Mapa() {
    for (auto o: objetos) {
        delete (o);
    }
    for (auto o: diagonalesDer) {
        delete (o);
    }
    for (auto o: diagonalesIzq) {
        delete (o);
    }
}
