#include "player.h"
#include <iostream>

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
	m_decelerate = false;
}
void Player::Areleased() {
	m_left = false;
}
void Player::Dreleased() {
	m_right = false;
}

void Player::update(float elapsedTime) {
	if (m_accelerate) {
		if (m_speed >= 0 && m_speed > 100) {
			m_speed += 3000 / m_speed;
		}
		if (m_speed >= 100 && m_speed > 200) {
			m_speed += 2000 / m_speed;
		}
		if (m_speed >= 200 && m_speed >= 300) {
			m_speed += 1000 / m_speed;
		}
		if (m_speed <= MAX_SPEED) {
			m_speed = MAX_SPEED;
		}
	}

	if (m_decelerate) {
		if (m_speed >= 0 && m_speed > 100) {
			m_speed -= 10*elapsedTime;
		}
		if (m_speed >= 100 && m_speed > 200) {
			m_speed -= 20*elapsedTime;
		}
		if (m_speed >= 200 && m_speed >= 300) {
			m_speed -= 30*elapsedTime;
		}
		if (m_speed <= 0) {
			m_speed = 0;
		}
	}
	if (!(m_left && m_right)) {
		m_sprite.setRotation(sf::degrees(0));
	}
	if (m_left) {
		m_sprite.setPosition({ m_sprite.getPosition().x - (50 * elapsedTime), 650 });
		if (m_sprite.getPosition().x < 88 + 180 + 30) {
			m_sprite.setPosition({ 88+180+15, 650 });
		}
		m_sprite.setRotation(sf::degrees(360 - 30));
		//std::cout << "Position of car: ( " << m_sprite.getPosition().x << " , " << m_sprite.getPosition().y << " )\n";
	}
	if (m_right) {
		m_sprite.setPosition({ m_sprite.getPosition().x + (50 * elapsedTime), 650 });
		if (m_sprite.getPosition().x > 335+180+30) {
			m_sprite.setPosition({ 335+180-15, 650 });
		}
		m_sprite.setRotation(sf::degrees(30));
		//std::cout << "Position of car: ( " << m_sprite.getPosition().x << " , " << m_sprite.getPosition().y << " )\n";
	}
}