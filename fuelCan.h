#pragma once
#include <SFML/Graphics.hpp>

class fuelCan {

private:
	//texture of oil patch 33,54 23,28
	sf::Texture m_texture;
	//sprite
	sf::Sprite m_sprite;
	//position
	sf::Vector2f m_position;

	sf::FloatRect bounds;
	sf::Vector2f size;

public:

	fuelCan();

	void spawnFuelCan(int seed);

	sf::Sprite getFuelCan();

	sf::FloatRect getBounds();

	bool updateFuelCan(float elapsedTime, float speed);

};