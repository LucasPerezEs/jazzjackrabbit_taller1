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
            Piso* piso = new Piso(j*2, (39-i)*2, 2, 1);
            objetos.push_back(piso);
            if ((tilemap[i][j] == 256 || tilemap[i][j] == 257) && piso->x > 8 && piso->x < 30 && piso->y > 3 && piso->y > 15)
            std::cout << "Soy un piso y mi x1 es: " << piso->x << " mi x2 es: " << piso->w << " mi y1 es: " << piso->y << " mi y2 es: " << piso->h << std::endl;
        }
    }
}
    //Piso* piso = new Piso(0, -1, 1000, 0);   // posicion.x posicion.y posicion.x2 posicion.y2
    //Piso* piso2 = new Piso(10, 0, 5, 40);  // pared derecha
    //Piso* piso3 = new Piso(0, 0, 1, 40);     // pared izquierda
    //Piso* piso4 = new Piso(20, 10, 35, 11);  // plataforma
    //Piso* piso5 = new Piso(0, 20, 1000, 0);
    //objetos.push_back(piso);
    //objetos.push_back(piso2);
    //objetos.push_back(piso3);
    //objetos.push_back(piso4);
    //objetos.push_back(piso5);
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
