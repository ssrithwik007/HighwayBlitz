#pragma once
#include <SFML/Graphics.hpp>

class HUD {

private:
	//font
	sf::Font m_font;
	//texts
	sf::Text m_score;
	sf::Text m_speed;
	sf::Text m_fuel;
	//character size
	int m_charSize = 10;
	//sprites
	//sf::Sprite m_fuelBar;


public:
	
	HUD();

	void displayHUD(int score, float speed, float fuel);

	sf::Text getScoreText();
	sf::Text getScoreText();
	sf::Text getScoreText();
};