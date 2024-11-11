#pragma once
#include <SFML\Graphics.hpp>
#include "Collisionable.h"
#include "Projectile.h"
#include "Player.h"

class Enemy : public sf::Drawable, public Collisionable
{
    std::vector<Projectile> projectiles;
public:
    Enemy();
    sf::Vector2f _newPos;
    sf::Sprite _sprite;
    sf::Texture _texture;
    int _timeRespawn;
    int _health;
    void update(Player& player);
    bool isCollision(std::vector<Projectile>& projectiles);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void hurt();
    void dies();
    sf::FloatRect getBounds() const override;
};

