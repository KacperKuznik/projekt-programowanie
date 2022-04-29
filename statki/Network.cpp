#pragma once
#include <SFML/Network.hpp>
#include <iostream>

using namespace std;
class Network {
private:
	sf::UdpSocket socket;
    int row, col;
    sf::Packet packet;
    sf::IpAddress sender;
    unsigned short port;
    unsigned short receiver_port;

public:
    Network()
    {
        if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
        {
            // error...
        }
        cout << "created socket at port: " << socket.getLocalPort() << endl; 
        socket.setBlocking(false);
    }
    auto listen() {
        struct result { sf::Socket::Status status; sf::Packet packet; };
        sf::Socket::Status status = socket.receive(packet, sender, port);
        return result{  status, packet };
    }
    void set_reciever_port(unsigned short _receiver_port) {
        receiver_port = _receiver_port;
    }
    void send(int row, int col) {
        packet << row << col;
        socket.send(packet, "127.0.0.1", receiver_port);
    }
};