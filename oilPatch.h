#pragma once
#include <SFML/Graphics.hpp>

class oilPatch {

private:
	//texture of oil patch 3,54 24,67
	sf::Texture m_texture;
	//sprite
	sf::Sprite m_oilPatch;
	//position
	sf::Vector2f m_position;

	sf::FloatRect bounds;
	sf::Vector2f size;

public:

	oilPatch(int seed);

	sf::Sprite getOilPatch();

	sf::FloatRect getBounds();

	void updateOilPatch(float elapsedTime, float speed, int seed);

};