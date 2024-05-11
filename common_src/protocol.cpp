#include "protocol.h"

#include <utility>

#include "desconection.h"
#include "liberror.h"

#define CHAR_SIZE 1
#define SHORT_SIZE 2

Protocol::Protocol(Socket peer): socket(std::move(peer)) {}


//Pre:
//Post: Envia un char por medio del socket del protocolo.
void Protocol::sendUChar(unsigned char c) {
    bool was_closed;
    socket.sendall(&c, CHAR_SIZE, &was_closed);
    if (was_closed) {
        throw ProtocolDesconection("No se pudo enviar el mensaje del cliente, "
                                   "el socket del server_src se cerro");
    }
}

//Pre:
//Post: Recive un char por medio del socket del protocolo.
unsigned char Protocol::receiveUChar() {
    bool was_closed;
    unsigned char c;
    socket.recvall(&c, CHAR_SIZE, &was_closed);
    if (was_closed) {
        throw ProtocolDesconection("Lectura de socket cerrado");
    }
    return c;
}

//Pre:
//Post: Envia un entero de 16 bits sin signo por el socket del protocolo.
void Protocol::send16(uint16_t v) {
    bool was_closed;
    uint16_t vn = htons(v);
    socket.sendall(&vn, SHORT_SIZE, &was_closed);
    if (was_closed) {
        throw ProtocolDesconection("Escritura en socket cerrado");
    }
}

//Pre:
//Post: Recive un entero de 16 bits sin signo por el socket del protocolo.
uint16_t Protocol::receive16() {
    bool was_closed;
    uint16_t res;
    socket.recvall(&res, SHORT_SIZE, &was_closed);
    if (was_closed) {
        throw ProtocolDesconection("Lectura de socket cerrado");
    }
    return ntohs(res);
}

//Pre:
//Post: Envia un string por el socket del protocolo.
void Protocol::sendString(const std::string& string) {
    bool was_closed;
    send16(string.size());
    socket.sendall(&string[0], string.size(), &was_closed);
    if (was_closed) {
        throw ProtocolDesconection("Escritura en socket cerrado");
    }
}

//Pre:
//Post: Recive un string por el socket del protocolo.
std::string Protocol::receiveString() {
    bool was_closed = false;
    uint16_t lenght = receive16();
    std::string string(lenght, ' ');
    socket.recvall(&string[0], lenght, &was_closed);
    if (was_closed) {
        throw ProtocolDesconection("Lectura de socket cerrado");
    }
    return string;
}

//Pre:
//Post: Cierra el socket del protocolo.
void Protocol::stop() {
    socket.shutdown(SHUT_RDWR);
    socket.close();
}

void Protocol::close() { socket.close(); }
