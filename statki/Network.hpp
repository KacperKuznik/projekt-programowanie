#pragma once

#include "SFML/Network.hpp"
#include <iostream>

class Network {
private:
    sf::UdpSocket socket;
    int row, col;
    sf::Packet packet;
    sf::IpAddress sender;
    unsigned short port;
    unsigned short receiverPort;
    sf::IpAddress receiverIp;

public:
    Network();

    struct Result {
        sf::Socket::Status status;
        sf::Packet packet;
    };

    Result listen();
    void setReceiverPort(unsigned short receiverPort);
    void setReceiverIp(const sf::String& receiverIp);
    void send(int row, int col);
    void connect(bool isStarting);
    void reply(bool isHit);
    unsigned short getPort() const;
};
