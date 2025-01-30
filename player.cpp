#include "player.h"
#include <iostream>
#include <cmath>

Player::Player() 
	: m_sprite(m_texture)
{
	m_speed = 0;
	m_accln = 0;
	m_position = { 95 * 2,325 * 2 };

	m_texture.loadFromFile("textures/textures-1.png.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect({ 0,0 }, { 28,49 }));

	m_sprite.setOrigin({ 14,25 });
	m_sprite.setPosition({ 211 + 180 ,325*2 });
}

sf::Sprite Player::getsprite() {
	return m_sprite;
}

sf::FloatRect Player::getPosition() {
	return m_sprite.getGlobalBounds();
}

float Player::getspeed() {
	return m_speed;
}

float Player::getaccln() {
	return m_accln;
}

float Player::getdccln() {
	return m_dccln;
}

void Player::Wpressed() {
	m_accelerate = true;
}
void Player::Spressed() {
	m_decelerate = true;
	m_brake = true;
}
void Player::Apressed() {
	m_left = true;
}
void Player::Dpressed() {
	m_right = true;
}
void Player::Wreleased() {
	m_accelerate = false;
	m_decelerate = true;
}
void Player::Sreleased() {
	m_decelerate = true;
	m_brake = false;
}
void Player::Areleased() {
	m_left = false;
}
void Player::Dreleased() {
	m_right = false;
}

void Player::update(float elapsedTime) {

	float acceleration = fmin(20 + 0.1 * m_speed, 60);
	if (m_accelerate) {
		if (m_speed == 0) {
			m_speed = 10;
		}
		else {
			m_speed += acceleration * elapsedTime * 10;
		}
		if (m_speed >= MAX_SPEED) {
			m_speed = MAX_SPEED;
		}
		//std::cout<< "acceleration: " << acceleration << " " << "Speed = " << m_speed << "\n";
	}

	if (m_decelerate) {
			m_speed -= 10*elapsedTime;
		if (m_speed <= 0) {
			m_speed = 0;
		}
		//std::cout<< "deccelerate: " << m_decelerate << " " << "Speed = " << m_speed << "\n";
	}

	if (m_brake) {
		m_speed -= 1;
		if (m_speed <= 0) {
			m_speed = 0;
		}
		//std::cout<< "brake: " << m_brake << " " << "Speed = " << m_speed << "\n";
	}

	/*if (!(m_left && m_right)) {
		m_sprite.setRotation(sf::degrees(0));
	}
	sf::Angle turningAngle = sf::degrees(45 * (1-(m_speed / MAX_SPEED)));
	float turningSpeed = 100/(1+0.002f*(m_speed));
	*/
	if (m_left) {
		m_sprite.setPosition({ m_sprite.getPosition().x - (50 * elapsedTime), 650 });
		if (m_sprite.getPosition().x < 88 + m_xOffset + 15) {
			m_sprite.setPosition({ 88 + m_xOffset + 15, 650 });
		}
		//m_sprite.setRotation(sf::degrees(360 - turningAngle.asDegrees()));
		//std::cout << "left - " << turningAngle.asDegrees() << "\n";
		//std::cout << "Position of car: ( " << m_sprite.getPosition().x << " , " << m_sprite.getPosition().y << " )\n";
	}
	if (m_right) {
		m_sprite.setPosition({ m_sprite.getPosition().x + (50 * elapsedTime), 650 });
		if (m_sprite.getPosition().x > 335 + m_xOffset - 15) {
			m_sprite.setPosition({ 335 + m_xOffset - 15, 650 });
		}
		//m_sprite.setRotation(turningAngle);
		//std::cout << "right - " << turningAngle.asDegrees() << "\n";
		//std::cout << "Position of car: ( " << m_sprite.getPosition().x << " , " << m_sprite.getPosition().y << " )\n";
	}
}