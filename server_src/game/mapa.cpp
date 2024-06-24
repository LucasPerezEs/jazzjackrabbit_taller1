#include "../headers/mapa.h"

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
            //cargarCSV("../client_src/assets/background/castle_erlong_map/castle_earlong_mapa.csv");

    for (std::vector<int>::size_type i = tilemap.size() - 1; i >= 1; --i) {
        for (std::vector<int>::size_type j = 0; j < tilemap[i].size(); j++) {
            if (tilemap[i][j] != -1) {

                /*if (tilemap[i][j] == 20000) {
                    DiagonalIzquierda* diagonal = new DiagonalIzquierda(j, (tilemap.size()-1-i), 1,
                1); diagonalesIzq.push_back(diagonal);
                }
                else if (tilemap[i][j] == 22000) {
                    DiagonalDerecha* diagonal = new DiagonalDerecha(j, (tilemap.size()-1-i), 1, 1);
                    diagonalesDer.push_back(diagonal);
                }
                */
                if (tilemap[i][j] == 147) {
                    DiagonalIzquierda* diagonal =
                            new DiagonalIzquierda(j, (tilemap.size() - 1 - i), 1, 1);
                    diagonalesIzq.push_back(diagonal);
                } else if (tilemap[i][j] == 142) {
                    DiagonalDerecha* diagonal =
                            new DiagonalDerecha(j, (tilemap.size() - 1 - i), 1, 1);
                    diagonalesDer.push_back(diagonal);
                } else if ((tilemap[i][j] < 40 && tilemap[i][j] > 0) ||
                           (tilemap[i][j] >= 140 && tilemap[i][j] < 200)) {
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
