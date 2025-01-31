#include "oilPatch.h"

oilPatch::oilPatch(int seed)
	:m_oilPatch(m_texture)
{
	//load texture
	m_texture.loadFromFile("textures/textures-1.png.png");
	//initialize the oil  patch
	m_oilPatch.setTexture(m_texture);
	m_oilPatch.setTextureRect(sf::IntRect({ 3,54 }, { 22,14 }));
	m_oilPatch.setScale({ 2.f,2.f });
	bounds = m_oilPatch.getLocalBounds();
	size = bounds.size;
	m_oilPatch.setOrigin({ size.x/2 , size.y/2 });
	srand(seed);
	m_position.x = (float)(rand() % ((88 + (int)(size.x/2)) - (335 - (int)(size.x/2)) + 1) + (88 + 11 + 180));
	m_position.y = (float) - 7;
	m_oilPatch.setPosition(m_position);
}

sf::Sprite oilPatch::getOilPatch() {
	return m_oilPatch;
}

sf::FloatRect oilPatch::getBounds() {
	return m_oilPatch.getGlobalBounds();
}

void oilPatch::updateOilPatch(float elapsedTime, float speed, int seed) {

	m_position.y += speed * elapsedTime;
	if (m_position.y > 807) {
		srand(seed);
		m_position.x = (float)(rand() % ((88 + (int)(size.x / 2)) - (335 - (int)(size.x / 2)) + 1) + (88 + 11 + 180));
		m_position.y = (float)-7;
	}
	m_oilPatch.setPosition(m_position);

}