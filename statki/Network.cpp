#include "Network.hpp"
#include <iostream>

Network::Network() {
    if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
        // Handle socket bind error if needed
    }
    std::cout << "Created socket at port: " << socket.getLocalPort() << std::endl;
    socket.setBlocking(false);
}

Network::Result Network::listen() {
    sf::Socket::Status status = socket.receive(packet, sender, port);

    if (!receiverPort || receiverIp.toString().empty()) {
        setReceiverIp(sender.toString());
        setReceiverPort(port);
    }

    return { status, packet };
}

void Network::setReceiverPort(unsigned short receiverPort) {
    this->receiverPort = receiverPort;
}

void Network::setReceiverIp(const sf::String& receiverIp) {
    this->receiverIp = sf::IpAddress(receiverIp);
}

void Network::send(int row, int col) {
    packet.clear();
    packet << row << col;
    socket.send(packet, receiverIp, receiverPort);
}

void Network::connect(bool isStarting) {
    std::cout << "\nConnecting with " << receiverIp << " on port " << receiverPort;
    packet.clear();
    packet << isStarting;
    socket.send(packet, receiverIp, receiverPort);
}

void Network::reply(bool isHit) {
    packet.clear();
    packet << isHit;
    socket.send(packet, receiverIp, receiverPort);
}

unsigned short Network::getPort() const {
    return socket.getLocalPort();
}
