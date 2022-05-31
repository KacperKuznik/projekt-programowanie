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
    sf::IpAddress receiver_ip;

public:
    Network()
    {
        if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
        {

        }
        cout << "created socket at port: " << socket.getLocalPort() << endl; 
        socket.setBlocking(false);
    }
    auto listen() {
        struct result { sf::Socket::Status status; sf::Packet packet; };
        sf::Socket::Status status = socket.receive(packet, sender, port);
        if (!receiver_port || receiver_ip.toString() == "") {
            set_reciever_ip(sender.toString());
            set_reciever_port(port);
        }
        return result{  status, packet };
    }
    void set_reciever_port(unsigned short _receiver_port) {
        receiver_port = _receiver_port;
    }
    void set_reciever_ip(sf::String _receiver_ip) {
        receiver_ip = sf::IpAddress(_receiver_ip);
    }
    void send(int row, int col) {
        packet.clear();
        packet << row << col;
        socket.send(packet, receiver_ip, receiver_port);
    }
    void connect(bool isStarting) {
        std::cout << "\nConnecting with " << receiver_ip << "on port " << receiver_port;
        packet.clear();
        packet << isStarting;
        socket.send(packet, receiver_ip, receiver_port);
    }
    void reply(bool isHit) {
        packet.clear();
        packet << isHit;
        socket.send(packet, receiver_ip, receiver_port);
    }
    unsigned short getPort(){
        return socket.getLocalPort();
    }

};