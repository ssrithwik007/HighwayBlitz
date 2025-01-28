#include <SFML/Graphics.hpp>
#include "player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 600, 800 }), "Highway Blitz");
    sf::Texture t_road("textures/road_texture.png");
    sf::Sprite road1(t_road);
    sf::Sprite road2(t_road);
    road1.setPosition({ 180,0 });
    road2.setPosition({ 180,-799 });

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
        road1.setPosition({ road1.getPosition().x,road1.getPosition().y + (player.getspeed() * dtAsS/10) });
        road2.setPosition({ road2.getPosition().x,road2.getPosition().y + (player.getspeed() * dtAsS/10) });
        if (road1.getPosition().y > 800) {
            road1.setPosition({ road1.getPosition().x,-798 });
        }
        if (road2.getPosition().y > 800) {
            road2.setPosition({ road2.getPosition().x,-798 });
        }


        window.clear();
        window.draw(road1);
        window.draw(road2);
        window.draw(player.getsprite());
        window.display();
    }
}