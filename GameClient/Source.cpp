#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>


using namespace std;

enum PacketType {
	TPing = 0,
	TId
};

int main() {

	sf::TcpSocket socket;
	sf::IpAddress ipAddr = sf::IpAddress("127.0.0.1");
	int port = 53000;
	sf::Socket::Status status = socket.connect(ipAddr, port);
	if (status != sf::Socket::Done)
	{
		cout << "error connecting to socket " << port << " at IP " << ipAddr << endl;
	}
	else {
		cout << "connected to socket " << port << " at IP " << ipAddr << endl;
	}

	sf::Packet packet;
	packet << '0';
	while (1) {
		if (socket.send(packet) == sf::Socket::Disconnected) {
			cout << "disconnected from server..." << endl;
			break;
		}
	}

	socket.disconnect();

	return 0;
}