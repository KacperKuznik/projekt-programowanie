#include "Ship.hpp"

Ship::Ship(short int _length, int x, int y) {
	length = _length;
	ship_tiles = new Tile[length];

	for (int i = 0; i < length; i++) {
		Tile tile(tile_width, shipColor);
		tile.setPosition(x + tile_width * i, y);
		ship_tiles[i] = tile;

	}

}

void Ship::drawShip(sf::RenderWindow& window) {


	for (int i = 0; i < length; i++) {

		window.draw(ship_tiles[i]);

	}
}

Tile Ship::getTile(int i) {
	return ship_tiles[i];
}

void Ship::chColor(sf::Color color) {
	for (int i = 0; i < length; i++) {
		ship_tiles[i].setFillColor(color);
	}
}

void Ship::hit(int i) {
	if (!ship_tiles[i].isHit()) {
		ship_tiles[i].setFillColor(shipHitColor);
		ship_tiles[i].setHit();
		isSunk();
	}
}

int Ship::size() {
	return length;
}

bool Ship::isSunk() {
	for (int i = 0; i < length; i++) {
		if (!ship_tiles[i].isHit()) {
			return false;
		}
	}
	chColor(shipSunkColor);
	return true;
}

void Ship::setPos(sf::Vector2f position) {
	if (rotation == 0) {
		for (int i = 0; i < length; i++) {
			ship_tiles[i].setPosition(position.x + tile_width * i, position.y);
		}
	}
	else {
		for (int i = 0; i < length; i++) {
			ship_tiles[i].setPosition(position.x, position.y + tile_width * i);
		}
	}
}

int Ship::chRot() {
	sf::Vector2f position = ship_tiles[0].getPosition();
	if (rotation == 0) {
		for (int i = 0; i < length; i++) {
			ship_tiles[i].setPosition(position.x, position.y + tile_width * i);
		}
		return 1;

	}
	else {
		for (int i = 0; i < length; i++) {
			ship_tiles[i].setPosition(position.x + tile_width * i, position.y);
		}
		return 0;
	}
}

bool Ship::getRot() {
	return rotation;
}

void Ship::setRot(bool _rotation) {
	rotation = _rotation;
}

void Ship::setShipToPlaced() {
	isPlaced = true;
}

bool Ship::checkPlacedState() {
	return isPlaced;
}
