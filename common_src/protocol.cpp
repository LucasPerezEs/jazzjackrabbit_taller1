#include "headers/protocol.h"

#include <utility>

#include "headers/desconection.h"
#include "headers/liberror.h"


#define CHAR_SIZE 1
#define SHORT_SIZE 2

Protocol::Protocol(Socket peer): socket(std::move(peer)) {}


// Pre:
// Post: Envia un char por medio del socket del protocolo.
void Protocol::sendUChar(unsigned char c) {
    bool was_closed;
    socket.sendall(&c, CHAR_SIZE, &was_closed);
    if (was_closed) {
        throw ProtocolDesconection("No se pudo enviar el mensaje del cliente, "
                                   "el socket del server_src se cerro");
    }
}

// Pre:
// Post: Recive un char por medio del socket del protocolo.
unsigned char Protocol::receiveUChar() {
    bool was_closed;
    unsigned char c;
    socket.recvall(&c, CHAR_SIZE, &was_closed);
    if (was_closed) {
        throw ProtocolDesconection("Lectura de socket cerrado");
    }
    return c;
}

// Pre:
// Post: Envia un entero de 16 bits sin signo por el socket del protocolo.
void Protocol::send16(uint16_t v) {
    bool was_closed;
    uint16_t vn = htons(v);
    socket.sendall(&vn, SHORT_SIZE, &was_closed);
    if (was_closed) {
        throw ProtocolDesconection("Escritura en socket cerrado");
    }
}

// Pre:
// Post: Recive un entero de 16 bits sin signo por el socket del protocolo.
uint16_t Protocol::receive16() {
    bool was_closed;
    uint16_t res;
    socket.recvall(&res, SHORT_SIZE, &was_closed);
    if (was_closed) {
        throw ProtocolDesconection("Lectura de socket cerrado");
    }
    return ntohs(res);
}

// Pre:
// Post: Envia un string por el socket del protocolo.
void Protocol::sendString(const std::string& string) {
    bool was_closed;
    send16(string.size());
    socket.sendall(&string[0], string.size(), &was_closed);
    if (was_closed) {
        throw ProtocolDesconection("Escritura en socket cerrado");
    }
}

// Pre:
// Post: Recive un string por el socket del protocolo.
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

// Pre:
// Post: Cierra el socket del protocolo.
void Protocol::stop() {
    socket.shutdown(SHUT_RDWR);
    socket.close();
}

// Pre:
// Post: Recive un entero de 32 bits sin signo por el socket del protocolo.
uint32_t Protocol::receiveUInt32() {
    bool was_closed;
    uint32_t res;
    socket.recvall(&res, sizeof(uint32_t), &was_closed);
    if (was_closed) {
        throw ProtocolDesconection("Lectura de socket cerrado");
    }
    return ntohl(res);
}

void Protocol::send32(uint32_t v) {
    bool was_closed;
    uint32_t vn = htonl(v);
    socket.sendall(&vn, sizeof(uint32_t), &was_closed);
    if (was_closed) {
        throw ProtocolDesconection("Escritura en socket cerrado");
    }
}


void Protocol::sendBool(bool value) {
    unsigned char byte = value ? 1 : 0;
    sendUChar(byte);
}

// Recibir un bool
bool Protocol::receiveBool() {
    unsigned char byte = receiveUChar();
    return byte != 0;
}


std::vector<std::string> Protocol::receiveVectorString() {
    std::vector<std::string> vec;
    uint16_t size = receive16();
    vec.reserve(size);
    for (uint16_t i = 0; i < size; ++i) {
        vec.push_back(receiveString());
    }
    return vec;
}

void Protocol::sendVectorString(const std::vector<std::string>& vec){
    send16(vec.size());
    for (const auto& str : vec) {
        sendString(str);
    }
}

void Protocol::sendMap(const std::vector<std::vector<std::string>>& map){
    send16(map.size());
    for (const auto& innerVec : map) {
        send16(innerVec.size()); 
        for (const auto& str : innerVec) {
            sendString(str);
        }
    }
}

std::vector<std::vector<std::string>> Protocol::receiveMap(){

    std::vector<std::vector<std::string>> mapReceived;
    uint16_t numRows = receive16();

    for (uint16_t row = 0; row < numRows; ++row) {
        uint16_t numCols = receive16();
        std::vector<std::string> rowValues;

        for (uint16_t col = 0; col < numCols; ++col) {
            rowValues.push_back(receiveString());
        }

        mapReceived.push_back(rowValues);
    }

    return mapReceived;
}


std::vector<std::uint32_t> Protocol::receiveVectorUint32() {
    std::vector<std::uint32_t> vec;
    uint16_t size = receive16();
    vec.reserve(size);
    for (uint16_t i = 0; i < size; ++i) {
        vec.push_back(receiveUInt32());
    }
    return vec;
}

void Protocol::sendVectorUint32(const std::vector<std::uint32_t>& vec){
    send16(vec.size());
    for (const auto& str : vec) {
        send32(str);
    }
}


void Protocol::close() { socket.close(); }
