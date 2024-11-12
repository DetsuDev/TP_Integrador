#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <ctime>
#include <sstream>
#include <string>
#include <vector>
#include "Player.h"
#include "Coin.h"
#include "Enemy.h"
#include "Rat.h"  // Incluimos Rat para utilizarla

int main()
{


    std::srand((unsigned)std::time(0));
    int w_width = 1280;
    int w_height = 720;
    sf::RenderWindow window(sf::VideoMode(w_width, w_height), "TP Integrador", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);



    /// DIMENSIONES MAPA 640X512
    sf::Color backgroundColor(46, 46, 46);  // Color HSV: 060, 000, 018 convertido a RGB: (46, 46, 46)


    sf::View view;
    view.setSize(w_width * 0.5f, w_height * 0.5f); // Apply zoom (e.g., 0.8 for 20% zoom)
    view.setCenter(w_width / 2, w_height / 2);     // Start at the center of the screen

    sf::View uiView;
    uiView = window.getDefaultView();

    sf::Clock deltaTimeClock;

    sf::Sprite map_0, map_1, map_2, map_door;
    sf::Texture tex_0, tex_1, tex_2, tex_door;

    tex_0.loadFromFile("assets/textures/map/map_0.png");
    map_0.setTexture(tex_0);

    tex_1.loadFromFile("assets/textures/map/map_1.png");
    map_1.setTexture(tex_1);

    tex_2.loadFromFile("assets/textures/map/map_2.png");
    map_2.setTexture(tex_2);

    tex_door.loadFromFile("assets/textures/map/door_closed.png");
    map_door.setTexture(tex_door);


    sf::Font font;
    font.loadFromFile("assets/fonts/daydream.ttf");

    sf::Text textPoints, textEnemies, textLifes, textTime, textRound;
    textPoints.setFont(font);
    textEnemies.setFont(font);
    textLifes.setFont(font);
    textRound.setFont(font);
    textTime.setFont(font);

    Coin coin;
    coin.respawn();
    Player player;

    std::vector<Enemy*> enemies = { new Rat(), new Rat(), new Rat()};

    int points = 0;
    int timeCount = 1800;
    int roundCount = 1;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        float deltaTime = deltaTimeClock.restart().asSeconds();

        timeCount--;
        player.update(deltaTime);

        if (enemies.size() < 1 || timeCount <1)
        {
            roundCount++;
        }
        if (player.isCollision(coin))
        {
            coin.respawn();
            points++;
        }

        textPoints.setString("Puntos: " + std::to_string(points));
        textPoints.setPosition(10, 10);
        textPoints.setScale(0.5,0.5);
        textRound.setString("Numero Ronda: " + std::to_string(roundCount));
        textRound.setPosition((uiView.getSize().x - textRound.getGlobalBounds().width) / 2, 10);
        textRound.setScale(0.4,0.4);
        textTime.setString("Tiempo Ronda: " + std::to_string(timeCount/60));
        textTime.setPosition((uiView.getSize().x - textTime.getGlobalBounds().width) / 2, textRound.getPosition().y + textTime.getGlobalBounds().height + 10);
        textTime.setScale(0.4,0.4);
        textEnemies.setString("Enemigos restantes: " + std::to_string(enemies.size()));
        textEnemies.setPosition((uiView.getSize().x - textEnemies.getGlobalBounds().width) / 2, textTime.getPosition().y + textEnemies.getGlobalBounds().height + 10);
        textEnemies.setScale(0.4,0.4);
        textLifes.setString("Vidas: " + std::to_string(player.getLifes()));
        textLifes.setPosition(uiView.getSize().x - textLifes.getGlobalBounds().width - 10, 10);
        textLifes.setScale(0.5,0.5);


        map_door.setPosition((map_0.getGlobalBounds().width - map_door.getGlobalBounds().width) / 2,
                             (map_0.getGlobalBounds().height - map_0.getGlobalBounds().height + map_door.getGlobalBounds().height) / 2 - 8);

        view.setCenter(player.getPosition());
        window.setView(view);
        window.clear(backgroundColor);

        window.draw(map_0);
        window.draw(map_1);
        window.draw(coin);
        window.draw(player);
        window.draw(map_2);
        window.draw(map_door);
        for (int i = 0; i < enemies.size(); ++i)
        {
            window.draw(*enemies[i]);  // Dibuja cada enemigo del array

            enemies[i]->update(player);
            // Actualiza las vidas usando la clase Player
            if (/*player.isCollision(*enemies[i]) || */ enemies[i] -> isCollision(player.getProjectiles()))
            {
                player.hurt();  // Restar una vida del jugador
                enemies[i]->hurt(); // Daño y respawn en el enemigo
            }
            if (enemies[i] -> isDead())
            {
                delete enemies[i];
                enemies.erase(enemies.begin() + i);
                i--;
            }
        }

        window.setView(uiView);
        window.draw(textPoints);
        window.draw(textTime);
        window.draw(textRound);
        window.draw(textEnemies);
        window.draw(textLifes);

        window.display();
    }
    return 0;
}
