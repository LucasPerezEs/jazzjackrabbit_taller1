#include "client_class.h"

Client::Client(const std::string& hostname, const std::string& servername):
        client_protocol(hostname.c_str(), servername.c_str()) {}

void Client::run(std::istream& in) {
    std::string line;
    while (std::getline(in, line)) {
        if (line == "Atacar") {
            sendAttack();
        } else if (line.find("Leer") != std::string::npos) {
            int n = std::stoi(line.substr(COMMAND_PARAMETER_START_INDEX));
            receive_and_print_messages(n);

        } else if (line == "Salir") {
            break;
        } else {
            std::cout << "Comando desconocido: " << line << std::endl;
        }
    }
    client_protocol.stop();
}


void Client::sendAttack() { client_protocol.send_attack(); }


void Client::receive_and_print_messages(int n) {

        for (int i = 0; i < n; ++i) {
            EnemyEvent event;
            try {
                event = client_protocol.receive_enemy_event();
                printEvent(event);
            } catch (ProtocolError& pe) {
                printMessage("Evento desconocido.");
            }
        }
}

void Client::printEvent(EnemyEvent event) {
    std::string msg;
    switch (event.event_type) {
        case Event::DEATH:
            msg = "Un enemigo ha muerto. " + std::to_string(event.enemies_alive_cnt) +
                  " vivo(s) y " + std::to_string(event.enemies_dead_cnt) + " muerto(s).";
            break;
        case Event::ALIVE:
            msg = "Un enemigo ha revivido. " + std::to_string(event.enemies_alive_cnt) +
                  " vivo(s) y " + std::to_string(event.enemies_dead_cnt) + " muerto(s).";
            break;
        default:
            throw ProtocolError("Evento desconocido.");
    }

    printMessage(msg);
}

void Client::printMessage(const std::string& msg) { std::cout << msg << std::endl; }
