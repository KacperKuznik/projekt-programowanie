#include "Network.hpp"

Network::Network()
{
    if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
        std::cerr << "Error: Failed to bind socket to any port." << std::endl;
    }
    socket.setBlocking(false);
}

Network::~Network() {
    socket.unbind();
}

Network::Result Network::listen() {
    Result result;
    sf::Socket::Status status = socket.receive(result.packet, sender, port);

    if (!receiverPort || receiverIp.toString() == "") {
        setReceiverIp(sender.toString());
        setReceiverPort(port);
    }

    result.status = status;
    return result;
}

void Network::setReceiverPort(unsigned short _receiverPort) {
    receiverPort = _receiverPort;
}

void Network::setReceiverIp(sf::String _receiverIp) {
    receiverIp = sf::IpAddress(_receiverIp);
}

void Network::send(int row, int col) {
    packet.clear();
    packet << row << col;
    socket.send(packet, receiverIp, receiverPort);
}

void Network::connect(bool isStarting, std::string history_file_name) {
    History::addTextToFile(
        "Connecting game at IP address: " + History::to_string(receiverIp) + "\n" +
        "Connecting game at port number: " + History::to_string(receiverPort) + "\n\n",
        history_file_name
    );
    packet.clear();
    packet << isStarting;
    socket.send(packet, receiverIp, receiverPort);
}

void Network::reply(bool isHit) {
    packet.clear();
    packet << isHit;
    socket.send(packet, receiverIp, receiverPort);
}

unsigned short Network::getPort() {
    return socket.getLocalPort();
}
