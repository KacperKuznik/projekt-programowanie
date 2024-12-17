#pragma once

#include <SFML/Network.hpp>
#include "History.hpp"
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
    struct Result {
        sf::Socket::Status status;
        sf::Packet packet;
    };
    Network();
    ~Network();
    Result listen();
    void setReceiverPort(unsigned short receiverPort);
    void setReceiverIp(sf::String receiverIp);
    void send(int row, int col);
    void connect(bool isStarting, std::string history_file_name);
    void reply(bool isHit);
    unsigned short getPort();
};
