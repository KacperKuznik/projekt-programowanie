#pragma once

#include <SFML/Network.hpp>
#include <iostream>

class Network {
private:
    sf::UdpSocket socket;
    int row, col;
    sf::Packet packet;
    sf::IpAddress sender;
    unsigned short port;
    unsigned short receiver_port;
    sf::IpAddress receiver_ip;
public:
    struct Result {
        sf::Socket::Status status;
        sf::Packet packet;
    };
    Network();
    Result listen();
    void set_reciever_port(unsigned short _receiver_port);
    void set_reciever_ip(sf::String _receiver_ip);
    void send(int row, int col);
    void connect(bool isStarting);
    void reply(bool isHit);
    unsigned short getPort();
};
