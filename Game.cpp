#include "Game.h"

Game::Game()
	:road1(roadTexture), road2(roadTexture), m_score(m_font), m_speed(m_font), m_fuel(m_font), m_crashes(m_font), m_gameover(m_font)
{

	window.create(sf::VideoMode({ 600,800 }), "Highway Blitz");

	roadTexture.loadFromFile("textures/road_texture.png");
	m_font.openFromFile("fonts/ByteBounce.ttf");

	m_score.setFont(m_font);
	m_score.setFillColor(sf::Color::White);
	m_score.setString("Score: ");
	m_score.setCharacterSize(CHAR_SIZE);
	m_score.setPosition({ 5,5 });

	m_speed.setFont(m_font);
	m_speed.setFillColor(sf::Color::White);
	m_speed.setString("Speed: ");
	m_speed.setCharacterSize(CHAR_SIZE);
	m_speed.setPosition({ (float)5,(float)5 + CHAR_SIZE });

	m_fuel.setFont(m_font);
	m_fuel.setFillColor(sf::Color::White);
	m_fuel.setString("Fuel: ");
	m_fuel.setCharacterSize(CHAR_SIZE);
	m_fuel.setPosition({ (float)5,(float)5 + (2 * CHAR_SIZE) });

	m_crashes.setFont(m_font);
	m_crashes.setFillColor(sf::Color::White);
	m_crashes.setString("Crashes: ");
	m_crashes.setCharacterSize(CHAR_SIZE);
	m_crashes.setPosition({ (float)5,(float)5 + (3 * CHAR_SIZE) });

	m_gameover.setFont(m_font);
	m_gameover.setFillColor(sf::Color::White);
	m_gameover.setString("GAMEOVER\nPress Enter to exit");
	m_gameover.setCharacterSize(50);
	sf::FloatRect bounds = m_gameover.getLocalBounds();
	sf::Vector2f size = bounds.size;
	m_gameover.setOrigin({ size.x / 2,size.y / 2 });
	m_gameover.setPosition({ (float)window.getSize().x / 2, (float)window.getSize().y / 2 });

	int countFrames = 0;
	float roadSpeed = 0;
	int score = 0;
	float slideTime = 3;
	const int MAX_CRASHES = 3;
	int crashes = 0;
	const float MAX_FUEL = 31;
	float fuel = MAX_FUEL;
	bool fuelSpawned = false;

}

void Game::run() {

	while (window.isOpen()) {

		sf::Time dt = clock.restart();
		float elapsedTime = dt.asSeconds();

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
				window.close();
		}

		userInput();
		updateEntities(elapsedTime);

		if (checkCollision(player.getBounds(), m_oilPatch.getBounds())) {
			player.changePlayerState();
		}
		if (checkCollision(player.getBounds(), m_fuelCan.getBounds())) {
			fuelSpawned = false;
			fuel += 30;
			if (fuel > MAX_FUEL)   fuel = MAX_FUEL;
		}
	}

}

void Game::userInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		player.Wpressed();
	}
	else
	{
		player.Wreleased();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		player.Spressed();
	}
	else
	{
		player.Sreleased();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		player.Apressed();
	}
	else
	{
		player.Areleased();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		player.Dpressed();
	}
	else
	{
		player.Dreleased();
	}
}

void Game::updateEntities(float elapsedTime) {
	player.update(elapsedTime);
	roadSpeed = player.getspeed();
	road1.setPosition({ road1.getPosition().x,road1.getPosition().y + (roadSpeed * elapsedTime) });
	if (road1.getPosition().y >= 0) {
		road2.setPosition({ road2.getPosition().x,road1.getPosition().y - 800 });
	}
	else {
		road2.setPosition({ road2.getPosition().x,road1.getPosition().y + 800 });
	}
	if (road1.getPosition().y > 800) {
		road1.setPosition({ road1.getPosition().x,-799 });
	}
	if (road2.getPosition().y > 800) {
		road2.setPosition({ road2.getPosition().x,-799 });
	}
	/*std::cout << "Position of road1: ( " << road1.getPosition().x << " , " << road1.getPosition().y << " )\n";
	std::cout << "Position of road2: ( " << road2.getPosition().x << " , " << road2.getPosition().y << " )\n";
	std::cout << "r1 y + r2 y: " << abs(road1.getPosition().y) + abs(road2.getPosition().y) << "\n";*/

	srand(time(0));
	m_oilPatch.updateOilPatch(elapsedTime, roadSpeed, rand() % rand());
	if (fuelSpawned) {
		if (!(m_fuelCan.updateFuelCan(elapsedTime, roadSpeed))) {
			fuelSpawned = false;
		}
	}
}

bool Game::checkCollision(sf::FloatRect obj1, sf::FloatRect obj2) {
	std::optional<sf::FloatRect> intersection = obj1.findIntersection(obj2);
	return intersection.has_value();
}