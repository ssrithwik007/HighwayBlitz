#include "fuelCan.h"

fuelCan::fuelCan()
	:m_sprite(m_texture)
{
	//load texture
	m_texture.loadFromFile("textures/textures-1.png.png");
	//initialize the oil  patch
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect({ 33,54 }, { 23,28 }));
	m_sprite.setScale({ 1.5f,1.5f });
	bounds = m_sprite.getLocalBounds();
	size = bounds.size;
	m_sprite.setOrigin({ size.x / 2 , size.y / 2 });
	m_position.x = -100.f;
	m_position.y = -100.f;
	m_sprite.setPosition(m_position);
}

void fuelCan::spawnFuelCan(int seed) {

	srand(seed);
	m_position.x = (float)(rand() % ((88 + (int)(size.x / 2)) - (335 - (int)(size.x / 2)) + 1) + (88 + 11 + 180));
	m_position.y = (float)-size.y / 2;
	m_sprite.setPosition(m_position);
}

sf::Sprite fuelCan::getFuelCan() {
	return m_sprite;
}

sf::FloatRect fuelCan::getBounds() {
	return m_sprite.getGlobalBounds();
}

bool fuelCan::updateFuelCan(float elapsedTime, float speed) {

	m_position.y += speed * elapsedTime;
	if (m_position.y > 800+size.y/2) {
		return false;
	}
	m_sprite.setPosition(m_position);

}