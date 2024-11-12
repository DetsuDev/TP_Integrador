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
    virtual void respawn() = 0;
    virtual void update(Player& player) = 0;
    float scaleFactor = 0.5f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (1.5f - 0.5f)));

    bool isCollision(std::vector<Projectile>& projectiles);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void hurt();
    bool isDead();
    sf::FloatRect getBounds() const override;
};

