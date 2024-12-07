#include "PlayerGrid.hpp"

void PlayerGrid::mark(int row, int col, std::vector<Ship> ships, Network& network, Player& player) {
    for (int i = 0; i < ships.size(); i++) {
        for (int j = 0; j < ships[i].size(); j++) {
            if (isHit(row, col, ships[i].getTile(j))) {
                ships[i].hit(j);
                player.hit();
                network.reply(true);
                return;
            }
        }
    }
    network.reply(false);
    tiles[row][col].setFillColor(missedShotColor);
    player.changeTurn();
}

void PlayerGrid::placeShip(Ship& ship, sf::Vector2f mouse) {
    auto pos = getClickedPosition(mouse);
    if (pos.row >= 0 && pos.col >= 0) {
        if (ship.getRotation() == 0) {
            if (pos.row + ship.size() > 10) {
                // Ship cannot be placed, handle appropriately
            }
            else {
                sf::Vector2f xy = tiles[pos.row][pos.col].getPosition();
                ship.setPosition(xy);
            }
        }
        else {
            if (pos.col + ship.size() > 10) {
                // Ship cannot be placed, handle appropriately
            }
            else {
                sf::Vector2f xy = tiles[pos.row][pos.col].getPosition();
                ship.setPosition(xy);
            }
        }
    }
}

bool PlayerGrid::isHit(int row, int col, Tile tile) {
    if (tile.getGlobalBounds().contains(tiles[row][col].getCenter())) {
        return true;
    }
    return false;
}

bool PlayerGrid::canBeRotated(Ship ship) {
    auto pos = getClickedPosition(ship.getTile(0).getCenter());
    int size = ship.size();
    bool rotation = ship.getRotation();

    if (rotation == 0) {
        if (pos.col + size > 10) {
            return false;
        }
        else {
            return true;
        }
    }
    else {
        if (pos.row + size > 10) {
            return false;
        }
        else {
            return true;
        }
    }
}
