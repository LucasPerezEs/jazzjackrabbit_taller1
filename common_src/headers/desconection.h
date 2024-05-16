#ifndef PROTOCOL_DESCONECTION_H
#define PROTOCOL_DESCONECTION_H

#include <stdexcept>
#include <string>


class ProtocolDesconection: public std::runtime_error {
public:
    explicit ProtocolDesconection(const std::string& msg): runtime_error(msg) {}
};

#endif  // PROTOCOL_DESCONECTION_H
