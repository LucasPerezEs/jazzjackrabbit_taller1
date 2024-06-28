#include "../headers/map.h"

#include <cstdlib>

#include "../headers/bat.h"
#include "../headers/gem.h"
#include "../headers/ghost.h"
#include "../headers/gold_coin.h"
#include "../headers/monkey.h"

Floor::Floor(float posx, float posy, float width,
             float height) {  // Lo llame piso pero tambien puede ser una pared
    x = posx;
    y = posy;  // hitbox
    w = width;
    h = height;
}

bool Floor::colision(float posx, float posy, float width, float height) {
    if (x < (posx + width) && (x + w) > posx && y < (posy + height) && (y + h) > posy) {
        return true;
    }
    return false;
}


LeftDiagonal::LeftDiagonal(float posx, float posy, float width, float height) {
    x = posx;
    y = posy;  // hitbox
    w = width;
    h = height;
}

bool LeftDiagonal::colision(float posx, float posy, float width, float height) {
    if (x < (posx + width) && (x + w) > posx && y < (posy + height) && (y + h) > posy) {
        return true;
    }
    return false;
}


RightDiagonal::RightDiagonal(float posx, float posy, float width, float height) {
    x = posx;
    y = posy;  // hitbox
    w = width;
    h = height;
}

bool RightDiagonal::colision(float posx, float posy, float width, float height) {
    if (x < (posx + width) && (x + w) > posx && y < (posy + height) && (y + h) > posy) {
        return true;
    }
    return false;
}

std::vector<std::vector<int>> Map::cargarCSV(const std::string& ruta) {
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

Map::Map(const std::string& mapName) {

    std::string path = "../server_src/maps/" + mapName;
    std::vector<std::vector<int>> tilemap = cargarCSV(path);

    std::string spawn_path = "../server_src/maps/" + mapName + "_spawns";
    spawns = cargarCSV(spawn_path);
    for (auto spawn: spawns) {
        if (spawn[0] == 0) {
            spawnsPersonaje.emplace_back(spawn);
        } else {
            spawnsOtros.emplace_back(spawn);
        }
    }


    for (std::vector<int>::size_type i = 0; i < tilemap.size(); i++) {
        for (std::vector<int>::size_type j = 0; j < tilemap[i].size(); j++) {
            if (tilemap[i][j] != -1) {

                if (tilemap[i][j] == 18 || tilemap[i][j] == 29 || tilemap[i][j] == 47 ||
                    tilemap[i][j] == 58) {
                    LeftDiagonal* diagonal = new LeftDiagonal(j, (tilemap.size() - 1 - i), 1, 1);
                    diagonalesIzq.push_back(diagonal);

                } else if (tilemap[i][j] == 13 || tilemap[i][j] == 22 || tilemap[i][j] == 44 ||
                           tilemap[i][j] == 53) {
                    RightDiagonal* diagonal = new RightDiagonal(j, (tilemap.size() - 1 - i), 1, 1);
                    diagonalesDer.push_back(diagonal);

                } else if ((tilemap[i][j] < 70 && tilemap[i][j] > 0)) {
                    Floor* piso =
                            new Floor(j, (tilemap.size() - 1 - i), 1,
                                      1);  // cada numero en la matriz representa un espacio de 1x1
                    objetos.push_back(piso);
                }
            }
        }
    }
}

bool Map::CheckColision(
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

std::vector<int> Map::get_spawn(int type) {
    std::vector<int> res;
    if (type == 0 && spawnsPersonaje.size() > 0) {

        int i = rand() % spawnsPersonaje.size();
        res.emplace_back(spawnsPersonaje[i][2]);
        res.emplace_back(spawnsPersonaje[i][1]);
        return res;
    }

    res.emplace_back(-1);
    res.emplace_back(-1);
    return res;
}

Map::~Map() {
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
