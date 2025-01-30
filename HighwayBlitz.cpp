#include <SFML/Graphics.hpp>
#include "player.h"
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

    //font
    sf::Font m_font;
    m_font.openFromFile("fonts/ByteBounce.ttf");
    //texts
    sf::Text m_score(m_font);
    sf::Text m_speed(m_font);
    sf::Text m_fuel(m_font);
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
    m_fuel.setPosition({ (float)5,(float)5 + m_charSize + m_charSize });

    sf::Clock clock;

    Player player;

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
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

        float dtAsS = dt.asSeconds();

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

        m_score.setString("Score: " + std::to_string(score));
        m_speed.setString("Speed: " + std::to_string((int)player.getspeed()));
        m_fuel.setString("Fuel: ");



        window.clear();
        window.draw(road1);
        window.draw(road2);
        window.draw(player.getsprite());
        window.draw(m_score);
        window.draw(m_speed);
        window.draw(m_fuel);
        window.display();

        countFrames++;
        if (countFrames > 60) {
            score++;
            countFrames = 0;
        }
    }
}