#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "player.h"
#include "oilPatch.h"
#include "fuelCan.h"

class Game {

	sf::RenderWindow window;

	sf::Texture roadTexture;
	sf::Font m_font;

	sf::Sprite road1;
	sf::Sprite road2;

	sf::Text m_score;
	sf::Text m_speed;
	sf::Text m_fuel;
	sf::Text m_crashes;
	sf::Text m_gameover;
	const int CHAR_SIZE = 40;

	sf::Clock clock;

	int countFrames;
	float roadSpeed;
	int score;
	float slideTime;
	const int MAX_CRASHES = 3;
	int crashes;
	const float MAX_FUEL = 60;
	float fuel;
	bool fuelSpawned = false;

	Player player;
	oilPatch m_oilPatch = oilPatch(420);
	fuelCan m_fuelCan;

	Game();

	void run();
	
	void userInput();

	void updateEntities(float elapsedTime);

	void spawnFuelCan();

	void spawnOilPatch();

	bool checkCollision(sf::FloatRect obj1, sf::FloatRect obj2);

	void setStrings();

	void display();

	void gameOver();
};

