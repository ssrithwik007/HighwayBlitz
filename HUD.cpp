#include <string>
#include "HUD.h"

HUD::HUD() 
	: m_score(m_font), m_speed(m_font), m_fuel(m_font)
{
	//importing the font
	m_font.openFromFile("fonts/ByteBounce.ttf");

	m_score.setFillColor(sf::Color::White);
	m_score.setString("Score: ");
	m_score.setCharacterSize(m_charSize);
	m_score.setPosition({ 5,5 });

	m_speed.setFillColor(sf::Color::White);
	m_speed.setString("Speed: ");
	m_speed.setCharacterSize(m_charSize);
	m_speed.setPosition({ 5,5+m_charSize });

	m_fuel.setFillColor(sf::Color::White);
	m_fuel.setString("Fuel: ");
	m_fuel.setCharacterSize(m_charSize);
	m_fuel.setPosition({ 5,5+m_charSize+m_charSize});
}

void HUD::displayHUD(int score, float speed, float fuel){

	m_score.setString("Score: " + std::to_string(score));
	m_speed.setString("Speed: " + std::to_string((int)speed));
	m_fuel.setString("Fuel: ");

}

