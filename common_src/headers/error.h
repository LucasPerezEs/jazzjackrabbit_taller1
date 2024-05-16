#ifndef PROTOCOL_ERROR_H
#define PROTOCOL_ERROR_H
#include <stdexcept>
#include <string>

class ProtocolError: public std::runtime_error {
public:
    explicit ProtocolError(const std::string& msg): runtime_error(msg) {}
};
#endif  // PROTOCOL_ERROR_H
