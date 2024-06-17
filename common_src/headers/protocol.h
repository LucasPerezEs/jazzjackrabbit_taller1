#ifndef COMMON_PROTOCOL_H
#define COMMON_PROTOCOL_H

#include <cstdint>
#include <string>
#include <vector>

#include <arpa/inet.h>

#include "socket.h"


class Protocol {
protected:
    Socket socket;

public:
    explicit Protocol(Socket peer);

    void sendUChar(unsigned char c);
    unsigned char receiveUChar();

    void send16(uint16_t v);
    uint16_t receive16();

    void sendString(const std::string& string);
    std::string receiveString();

    uint32_t receiveUInt32();
    void send32(uint32_t v);

    void sendBool(bool value);
    bool receiveBool();

    void sendVectorString(const std::vector<std::string>& vec);
    std::vector<std::string> receiveVectorString();


    Protocol(const Protocol&) = delete;

    Protocol& operator=(const Protocol&) = delete;

    virtual void stop();

    virtual void close();

    virtual ~Protocol() = default;

};


#endif  // COMMON_PROTOCOL_H
