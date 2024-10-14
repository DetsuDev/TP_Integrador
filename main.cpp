#include <SFML/Graphics.hpp>
#include "Player.h"
int main()
{
    int w_height = 600;
    int w_width = 800;
    sf::RenderWindow window(sf::VideoMode(w_width, w_height), "TP Integrador");
    window.setFramerateLimit(60);

    Player player;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        // player.cmd();
        //player.draw(window);
        player.update();
        window.draw(player);
        window.display();
    }
    return 0;
}
