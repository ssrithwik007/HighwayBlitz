#include <SFML/Graphics.hpp>
#include "player.h"
#include "oilPatch.h"
#include "fuelCan.h"
#include <iostream>
#include <cmath>


int main()
{
    sf::RenderWindow window(sf::VideoMode({ 600, 800 }), "Highway Blitz");
    sf::Texture t_road("textures/road_texture.png");
    sf::Sprite road1(t_road);
    sf::Sprite road2(t_road);
    road1.setPosition({ 180,0 });
    road2.setPosition({ 180,-799 });
    int countFrames = 0;
    float roadSpeed;
    int score = 0;

    oilPatch m_oilPatch = oilPatch(420);
    std::cout << "Oil Patch created at position: " << m_oilPatch.getOilPatch().getPosition().x << "," << m_oilPatch.getOilPatch().getPosition().y << "\n";
    fuelCan m_fuelCan = fuelCan();
    std::cout << "Fuel Can created at position: " << m_fuelCan.getFuelCan().getPosition().x << "," << m_fuelCan.getFuelCan().getPosition().y << "\n";

    //font
    sf::Font m_font;
    m_font.openFromFile("fonts/ByteBounce.ttf");
    //texts
    sf::Text m_score(m_font);
    sf::Text m_speed(m_font);
    sf::Text m_fuel(m_font);
    sf::Text m_crashes(m_font);
    sf::Text m_gameover(m_font);
    //character size
    int m_charSize = 40;
    m_score.setFillColor(sf::Color::White);
    m_score.setString("Score: ");
    m_score.setCharacterSize(m_charSize);
    m_score.setPosition({ 5,5 });

    m_speed.setFillColor(sf::Color::White);
    m_speed.setString("Speed: ");
    m_speed.setCharacterSize(m_charSize);
    m_speed.setPosition({ (float)5,(float)5 + m_charSize });

    m_fuel.setFillColor(sf::Color::White);
    m_fuel.setString("Fuel: ");
    m_fuel.setCharacterSize(m_charSize);
    m_fuel.setPosition({ (float)5,(float)5 + (2 * m_charSize) });

    m_crashes.setFillColor(sf::Color::White);
    m_crashes.setString("Crashes: ");
    m_crashes.setCharacterSize(m_charSize);
    m_crashes.setPosition({ (float)5,(float)5 + (3 * m_charSize)});

    sf::Clock clock;

    Player player;
    float slideTime = 3;
    const int MAX_CRASHES = 3;
    int crashes = 0;
    const float MAX_FUEL = 31;
    float fuel = MAX_FUEL;
    bool fuelSpawned = false;

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        float dtAsS = dt.asSeconds();
        
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();
        }
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

        srand(time(0));
        if (fuel <= 29 && !(fuelSpawned)) {
            m_fuelCan.spawnFuelCan(rand());
            fuelSpawned = true;
        }

        sf::FloatRect oilBounds = m_oilPatch.getBounds();
        if (player.checkCollision(oilBounds) && player.getPlayerState() == "NORMAL") {
            player.changePlayerState();
            //crashes++;
        }

        sf::FloatRect fuelBounds = m_fuelCan.getBounds();
        if (player.checkCollision(fuelBounds)) {
            fuelSpawned = false;
            fuel += 30;
            if (fuel > MAX_FUEL)   fuel = MAX_FUEL;
        }
        
        player.update(dtAsS);
        roadSpeed = player.getspeed();
        road1.setPosition({ road1.getPosition().x,road1.getPosition().y + (roadSpeed * dtAsS) });
        if (road1.getPosition().y >= 0) {
            road2.setPosition({ road2.getPosition().x,road1.getPosition().y -800 });
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
        m_oilPatch.updateOilPatch(dtAsS, roadSpeed, rand()%rand());
        if (fuelSpawned) {
            if (!(m_fuelCan.updateFuelCan(dtAsS, roadSpeed))) {
                fuelSpawned = false;
            }
        }

        m_score.setString("Score: " + std::to_string(score));
        m_speed.setString("Speed: " + std::to_string((int)(player.getspeed()/2)));
        m_fuel.setString("Fuel: " + std::to_string((int)fuel));
        m_crashes.setString("Crashes: " + std::to_string(crashes));



        window.clear();
        window.draw(road1);
        window.draw(road2);
        window.draw(player.getsprite());
        window.draw(m_oilPatch.getOilPatch());
        window.draw(m_fuelCan.getFuelCan());
        window.draw(m_score);
        window.draw(m_speed);
        window.draw(m_fuel);
        window.draw(m_crashes);
        if (fuel <= 0.f) {
            m_gameover.setFillColor(sf::Color::White);
            m_gameover.setString("GAMEOVER\nPress Enter to exit");
            m_gameover.setCharacterSize(50);
            sf::FloatRect bounds = m_gameover.getLocalBounds();
            sf::Vector2f size = bounds.size;
            m_gameover.setOrigin({ size.x / 2,size.y / 2 });
            m_gameover.setPosition({ (float)window.getSize().x / 2, (float)window.getSize().y / 2 });
            window.draw(m_gameover);
            window.display();
            while (true) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                    window.close();
            }

        }
        window.display();

        fuel -= dtAsS;
        countFrames++;
        if (countFrames > 60) {
            if (player.getspeed() > 0) {
                score++;
            }
            countFrames = 0;
        }
    }
}