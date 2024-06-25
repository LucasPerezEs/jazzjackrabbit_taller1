#include <gtest/gtest.h>
#include "../common_src/headers/protocol.h"
#include "../client_src/headers/protocol.h"
#include "../server_src//headers/protocol.h"

class ProtocolTest: public ::testing::Test{
protected:
    Socket skt;
    ClientProtocol client_protocol;
    ServerProtocol server_protocol;


    inline ProtocolTest():
            skt("8080"),
            client_protocol("localhost","8080"),
            server_protocol(skt.accept()){}

    virtual ~ProtocolTest() {
        client_protocol.close();
        server_protocol.close();
        skt.close();
    }

};

TEST_F(ProtocolTest, SendReceiveUChar) {
    unsigned char send_char = 'a';
    client_protocol.sendUChar(send_char);
    unsigned char receive_char = server_protocol.receiveUChar();
    EXPECT_EQ(send_char, receive_char);
}

TEST_F(ProtocolTest, SendReceive16) {
    uint16_t send_value = 12345;
    client_protocol.send16(send_value);
    uint16_t receive_value = server_protocol.receive16();
    EXPECT_EQ(send_value, receive_value);
}

TEST_F(ProtocolTest, SendReceiveString) {
    std::string send_str = "hello";
    client_protocol.sendString(send_str);
    std::string receive_str = server_protocol.receiveString();
    EXPECT_EQ(send_str, receive_str);
}

TEST_F(ProtocolTest, SendReceiveUInt32) {
    uint32_t send_value = 4294967295; // Max uint32_t
    client_protocol.send32(send_value);
    uint32_t receive_value = server_protocol.receiveUInt32();
    EXPECT_EQ(send_value, receive_value);
}

TEST_F(ProtocolTest, SendReceiveBool) {
    bool send_bool = true;
    client_protocol.sendBool(send_bool);
    bool receive_bool = server_protocol.receiveBool();
    EXPECT_EQ(send_bool, receive_bool);
}

TEST_F(ProtocolTest, SendReceiveVectorString) {
    std::vector<std::string> send_vec = {"hello", "world"};
    client_protocol.sendVectorString(send_vec);
    std::vector<std::string> receive_vec = server_protocol.receiveVectorString();
    EXPECT_EQ(send_vec, receive_vec);
}

TEST_F(ProtocolTest, SendReceiveMap) {
    std::vector<std::vector<std::string>> send_map = {{"key1", "value1"}, {"key2", "value2"}};
    client_protocol.sendMap(send_map);
    std::vector<std::vector<std::string>> receive_map = server_protocol.receiveMap();
    EXPECT_EQ(send_map, receive_map);
}

TEST_F(ProtocolTest, SendReceiveVectorUInt32) {
    std::vector<std::uint32_t> send_vec = {1, 2, 3, 4, 5};
    client_protocol.sendVectorUint32(send_vec);
    std::vector<std::uint32_t> receive_vec = server_protocol.receiveVectorUint32();
    EXPECT_EQ(send_vec, receive_vec);
}