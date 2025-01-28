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
    float roadSpeed;

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
        road1.setPosition({ road1.getPosition().x,road1.getPosition().y + (roadSpeed * dtAsS/10) });
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


        window.clear();
        window.draw(road1);
        window.draw(road2);
        window.draw(player.getsprite());
        window.display();
    }
}