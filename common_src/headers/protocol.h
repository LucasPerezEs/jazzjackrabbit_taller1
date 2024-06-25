#ifndef COMMON_PROTOCOL_H
#define COMMON_PROTOCOL_H

#include <cstdint>
#include <string>
#include <vector>

#include <arpa/inet.h>

#include "entity_commands.h"
#include "socket.h"
#include "sound_commands.h"

struct AmmoData {
    EntityType ammo_type;
    // cppcheck-suppress unusedStructMember
    int ammo;
};

struct GameData {
    // cppcheck-suppress unusedStructMember
    int id;
    // cppcheck-suppress unusedStructMember
    float x;
    // cppcheck-suppress unusedStructMember
    float y;
    // cppcheck-suppress unusedStructMember
    float width;
    // cppcheck-suppress unusedStructMember
    float height;
    // cppcheck-suppress unusedStructMember
    int direction;
    AnimationType an;
    EntityType en;
    // cppcheck-suppress unusedStructMember
    int health;
    AmmoData ammo;
    // cppcheck-suppress unusedStructMember
    int score;
    // std::string name;
};

struct SoundData {
    EntityType entity;
    SoundType sound;
    // cppcheck-suppress unusedStructMember
    int id;
};


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

    void sendMap(const std::vector<std::vector<std::string>>& map);
    std::vector<std::vector<std::string>> receiveMap();


    std::vector<std::uint32_t> receiveVectorUint32();
    void sendVectorUint32(const std::vector<std::uint32_t>& vec);

    void sendGameData(const GameData& data);
    GameData receiveGameData();

    void sendSoundData(const SoundData& data);
    SoundData receiveSoundData();

    Protocol(const Protocol&) = delete;

    Protocol& operator=(const Protocol&) = delete;

    virtual void stop();

    virtual void close();

    virtual ~Protocol() = default;
};


#endif  // COMMON_PROTOCOL_H
