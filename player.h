#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class Player {

private:
	const float m_xOffset = 180;
	enum class State { NORMAL, SLIDING };
	std::map<State, std::string> stateToString = {
	{State::NORMAL, "NORMAL"},
	{State::SLIDING, "SLIDING"}
	};
	State playerState;
	// position of the car
	sf::Vector2f m_position;
	//speed of the car
	float m_speed;
	float MAX_SPEED = 600;
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
	const float SLIDE_TIME = 1;
	float slideTime;
	// controls
	bool m_accelerate;
	bool m_decelerate;
	bool m_left;
	bool m_right;
	bool m_brake;
	int turn;

public:

	Player();

	// get sprite
	sf::Sprite getsprite();

	// get position of the player car
	sf::FloatRect getBounds();
	
	//get speed of player car
	float getspeed();

	//get acceleration of player car
	float getaccln();

	//get deceleration of player car
	float getdccln();

	std::string getPlayerState();

	void changePlayerState();

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

	//checking collision
	bool checkCollision(sf::FloatRect objectBounds);

};