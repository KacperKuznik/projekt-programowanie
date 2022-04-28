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
    void listen() {

        sf::Socket::Status status = socket.receive(packet, sender, port);

        if (status == 0) {
            packet >> row >> col;
            cout << row << col << endl;
        }
    }

    void send(int row, int col, unsigned short port) {
        packet << row << col;
        socket.send(packet, "127.0.0.1", port);
    }
};