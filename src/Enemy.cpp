#include "Enemy.h"
#include "Projectile.h"
#include "Player.h"
#include <algorithm>
#include <cmath>  // Necesario para el c�lculo de la direcci�n

Enemy::Enemy()
{
    _texture.loadFromFile("assets/textures/enemy.png");
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2,_sprite.getGlobalBounds().height/2);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

void Enemy::hurt(){

}
bool Enemy::isCollision(std::vector<Projectile>& projectiles)
{
    for (size_t i = 0; i < projectiles.size(); ++i) {
        if (getBounds().intersects(projectiles[i].getBounds())) {  // Comprobamos la colisi�n
            hurt();  // Si hay colisi�n, el enemigo recibe da�o
            projectiles.erase(projectiles.begin() + i);  // El proyectil desaparece
            --i;  // Ajustar el �ndice despu�s de eliminar un proyectil
            return true;  // Si hubo una colisi�n, retornamos true
        }
    }
    return false;  // Si no hubo colisi�n, retornamos false
}

void Enemy::dies(){
    if (_health < 1)
        {
        delete this;
        }
}

sf::FloatRect Enemy::getBounds() const
{
    return _sprite.getGlobalBounds();
}

