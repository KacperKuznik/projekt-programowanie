#include "Network.hpp"

Network::Network()
{
    if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
        std::cerr << "Error: Failed to bind socket to any port." << std::endl;
    }
    else {
        std::cout << "created socket at port: " << socket.getLocalPort() << std::endl;
    }
    socket.setBlocking(false);
}

Network::Result Network::listen() {
    Result result;
    sf::Socket::Status status = socket.receive(result.packet, sender, port);

    if (!receiver_port || receiver_ip.toString() == "") {
        set_reciever_ip(sender.toString());
        set_reciever_port(port);
    }

    result.status = status;
    return result;
}

void Network::set_reciever_port(unsigned short _receiver_port) {
    receiver_port = _receiver_port;
}

void Network::set_reciever_ip(sf::String _receiver_ip) {
    receiver_ip = sf::IpAddress(_receiver_ip);
}

void Network::send(int row, int col) {
    packet.clear();
    packet << row << col;
    socket.send(packet, receiver_ip, receiver_port);
}

void Network::connect(bool isStarting) {
    std::cout << "\nConnecting with " << receiver_ip << "on port " << receiver_port;
    packet.clear();
    packet << isStarting;
    socket.send(packet, receiver_ip, receiver_port);
}

void Network::reply(bool isHit) {
    packet.clear();
    packet << isHit;
    socket.send(packet, receiver_ip, receiver_port);
}

unsigned short Network::getPort() {
    return socket.getLocalPort();
}
