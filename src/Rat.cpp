#include "Enemy.h"
#include "Rat.h"
#include <algorithm>
#include <cmath>  // Necesario para el c�lculo de la direcci�n

Rat::Rat()
{
    _texture.loadFromFile("assets/textures/rat.png");
    _timeRespawn = 60;
    _health = 3;
    respawn();
}


void Rat::respawn()
{
    _sprite.setPosition(32 + _sprite.getGlobalBounds().width, 16 + _sprite.getGlobalBounds().height);
    //_sprite.setPosition(std::rand()%500 + _sprite.getGlobalBounds().width, std::rand()%400 + _sprite.getGlobalBounds().height);

}

void Rat::update(Player& player)
{
    //Enemy::update(player);  // Llama a la funci�n update base si deseas extender el comportamiento
    _timeRespawn--;
    if (_timeRespawn<0)
    {
        _newPos = {std::rand()%500 + _sprite.getGlobalBounds().width, std::rand()%400 + _sprite.getGlobalBounds().height};

    }

    // Calculamos la direcci�n hacia el jugador
    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f enemyPos = _sprite.getPosition();

    // Calcular la diferencia en las posiciones (direcci�n)
    sf::Vector2f direction = playerPos - enemyPos;

    // Normalizar la direcci�n para que el enemigo se mueva de manera consistente (sin importar la distancia)
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)  // Evitar la divisi�n por cero
    {
        direction /= length;  // Normalizamos el vector

        // Movemos al enemigo hacia el jugador
        _sprite.move(direction * 3.5f);  // 5.0f es la velocidad de movimiento, ajusta si es necesario
    }
}
