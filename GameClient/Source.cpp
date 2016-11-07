#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>


using namespace std;

enum PacketType {
	TPing = 0,
	TId
};

struct Client {
	Client(sf::TcpSocket* socket) :
		socket(socket){

	};
	sf::TcpSocket* socket;
	int id() {
		return _id;
	}
	void connect(sf::IpAddress ipAddr, int port) {
		sf::Socket::Status status = socket->connect(ipAddr, port);
		if (status != sf::Socket::Done)
		{
			cout << "error connecting to socket " << port << " at IP " << ipAddr << endl;
		}
		else {
			cout << "connected to socket " << port << " at IP " << ipAddr << endl;
		}
	}
	sf::Socket::Status send(sf::Packet packet) {
		sf::Socket::Status status = socket->send(packet);
		if (status == sf::Socket::Disconnected) {
			cout << "disconnected from server..." << endl;
		}
		return status;
	}
	sf::Socket::Status receive(sf::Packet& packet) {
		sf::Socket::Status status = socket->receive(packet);
		if (status == sf::Socket::Disconnected) {
			cout << "disconnected from server..." << endl;
		}
		else if (status == sf::Socket::Done) {
			int type;
			packet >> type;
			cout << "received packet, Type: " << type;
			if (type == PacketType::TId) {
				packet >> _id;
				cout << ", Id: " << _id << endl;
			}
			else {
				cout << endl;
			}
		}
		else if (status == sf::Socket::Partial) {
			cout << "Partial packet received..." << endl;
		}
		return status;
	}

private:
	int _id;
};

int main() {

	sf::TcpSocket socket;
	Client client(&socket);
	client.connect(sf::IpAddress("127.0.0.1"), 53000);
	socket.setBlocking(false);

	sf::Packet packet;
	packet << '0';
	while (1) {
		if (client.receive(packet) == sf::Socket::Disconnected) {
			break;
		}
	}

	socket.disconnect();

	return 0;
}