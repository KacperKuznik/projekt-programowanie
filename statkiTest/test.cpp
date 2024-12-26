#include "pch.h"

#include "../statki/History.hpp"
#include "../statki/Tile.hpp"
#include "../statki/Ship.hpp"
#include "../statki/Grid.hpp"
#include "../statki/GridEnemy.hpp"
#include "../statki/GridPlayer.hpp"
#include "../statki/SoundManager.hpp"
#include "../statki/Button.hpp"
#include "../statki/Player.hpp"
#include "../statki/Network.hpp"
#include "../statki/Game.hpp"

#include "../statki/History.cpp"
#include "../statki/Tile.cpp"
#include "../statki/Grid.cpp"
#include "../statki/GridEnemy.cpp"
#include "../statki/GridPlayer.cpp"
#include "../statki/SoundManager.cpp"
#include "../statki/Button.cpp"
#include "../statki/Player.cpp"
#include "../statki/Network.cpp"
#include "../statki/Game.cpp"

#include "SFML/Graphics.hpp"

// ########################### History ############################
//TEST(HistoryClass, TestName) {
//	EXPECT_EQ(1, 1);
//	EXPECT_TRUE(true);
//}

// ############################# Tile #############################
TEST(TileClass, CenterWorks) {
	Tile tile(40, sf::Color::Blue);
	tile.setPosition(10, 10);
	EXPECT_EQ(tile.getCenter(), sf::Vector2f(30, 30));
}

//// ############################# Ship #############################
//TEST(ShipClass, TestName) {
//	EXPECT_EQ(1, 1);
//	EXPECT_TRUE(true);
//}

//// ############################# Grid #############################
//TEST(GridClass, TestName) {
//	EXPECT_EQ(1, 1);
//	EXPECT_TRUE(true);
//}

//// ########################## GridEnemy ###########################
//TEST(GridEnemyClass, TestName) {
//	EXPECT_EQ(1, 1);
//	EXPECT_TRUE(true);
//}

//// ########################## GridPlayer ##########################
//TEST(GridPlayerClass, TestName) {
//	EXPECT_EQ(1, 1);
//	EXPECT_TRUE(true);
//}

//// ######################### SoundManager #########################
//TEST(SoundManagerClass, TestName) {
//	EXPECT_EQ(1, 1);
//	EXPECT_TRUE(true);
//}

//// ############################ Button ############################
//TEST(ButtonClass, TestName) {
//	EXPECT_EQ(1, 1);
//	EXPECT_TRUE(true);
//}

// ############################ Player ############################
TEST(PlayerClass, HitWorks) {
	Player player(10);
	player.hit();
	EXPECT_EQ(player.getTilesCount(), 9);
	player.hit();
	player.hit();
	EXPECT_EQ(player.getTilesCount(), 7);
}

TEST(PlayerClass, ChangeTurnWorks) {
	Player player(10);
	EXPECT_EQ(player.isPlayerTurn(), false);
	player.changeTurn();
	EXPECT_EQ(player.isPlayerTurn(), true);
}

//// ########################### Network ############################
//TEST(NetworkClass, TestName) {
//	EXPECT_EQ(1, 1);
//	EXPECT_TRUE(true);
//}

//// ############################# Game #############################
//TEST(GameClass, TestName) {
//	EXPECT_EQ(1, 1);
//	EXPECT_TRUE(true);
//}
