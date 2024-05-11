
#include "controlador_cliente.h"

// Pre: -
// Post: -
ControladorCliente::ControladorCliente(const std::string& hostname, const std::string& servname):
        protocolo(hostname, servname) {}


// Pre: -
// Post: -
bool ControladorCliente::ejecutar_comando(char& cmd) {

    Command::ActionType accion;
    bool continuar_juego = true;

    switch (cmd) {
        case 'w':
            accion = Command::UP;
            std::cout << "Estoy subiendo" << std::endl;
            break;
        case 's':
            accion = Command::DOWN;
            std::cout << "Estoy bajando" << std::endl;
            break;
        case 'a':
            accion = Command::LEFT;
            std::cout << "Voy a la izquierda" << std::endl;
            break;
        case 'd':
            accion = Command::RIGHT;
            std::cout << "Voy a la derecha" << std::endl;
            break;
        case ' ':
            accion = Command::JUMP;
            std::cout << "Estoy saltando" << std::endl;
            break;
        case 'r':
            accion = Command::RUN;
            std::cout << "Estoy corriendo" << std::endl;
            break;
    }

    if(continuar_juego){
        Command cmd_obj;
        cmd_obj.action = accion;
        protocolo.send_command(cmd_obj);
    }

    return continuar_juego;
}