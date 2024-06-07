#include "headers/mapa.h"

Piso::Piso(float posx, float posy, float width,
           float height) {  // Lo llame piso pero tambien puede ser una pared
    x = posx;
    y = posy;  //hitbox
    w = width;
    h = height;
}

bool Piso::colision(float posx, float posy, float width, float height) {
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
    }

    return matriz;
}

Mapa::Mapa() {

    std::vector<std::vector<int>> tilemap = cargarCSV("../client_src/assets/background/medivo_map/Medivo_model_Terreno_solido.csv");

for (std::vector<int>::size_type i = tilemap.size()-1; i >= 1; --i) {
    for (std::vector<int>::size_type j = 0; j < tilemap[i].size(); j++) {
        if (tilemap[i][j] != -1) {
            Piso* piso = new Piso(j, (39-i), 1, 1); // cada numero en la matriz representa un espacio de 1x1
            objetos.push_back(piso);
            if ((tilemap[i][j] == 256 || tilemap[i][j] == 257) && piso->x > 8 && piso->x < 30 && piso->y > 3 && piso->y > 15)
        }
    }
}

}

bool Mapa::CheckColision(
        float x, float y, float w,
        float h) {  // devuelve true si la hitbox que le paso por parametro colisiona con el mapa
    for (auto p: objetos) {
        // cppcheck-suppress useStlAlgorithm
        if (p->colision(x, y, w, h)) {
            return true;
        }
    }
    return false;
}

Mapa::~Mapa() {
    for (auto o: objetos) {
        delete (o);
    }
}
