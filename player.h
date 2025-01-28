#pragma once
#include <SFML/Graphics.hpp>

class Player {

private:
	enum class State { NORMAL, SLIDING };
	// position of the car
	sf::Vector2f m_position;
	//speed of the car
	float m_speed;
	float MAX_SPEED = 300;
	// acceleration of the car
	float m_accln;
	// deceleration of car
	float m_dccln;
	// number of crashes
	int m_crashes;
	// player sprite
	sf::Sprite m_sprite;
	// car texture
	sf::Texture m_texture;
	// time since last crash or bump
	sf::Time timeSinceCrash;
	// controls
	bool m_accelerate;
	bool m_decelerate;
	bool m_left;
	bool m_right;

public:

	Player();

	// get sprite
	sf::Sprite getsprite();

	// get position of the player car
	sf::FloatRect getPosition();
	
	//get speed of player car
	float getspeed();

	//get acceleration of player car
	float getaccln();

	//get deceleration of player car
	float getdccln();

	//update the player car
	void update(float elapsedTime);

	//controls
	void Wpressed();
	void Dpressed();
	void Apressed();
	void Spressed();
	void Wreleased();
	void Dreleased();
	void Areleased();
	void Sreleased();

};