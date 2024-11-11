#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Collisionable.h"
#include <SFML/Graphics.hpp>

class Projectile {
public:
    Projectile(sf::Vector2f position, sf::Vector2f direction, float speed);
    void update(float deltaTime);
    void render(sf::RenderTarget& target) const;
    bool isOffScreen() const;
    sf::FloatRect getBounds() const;

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
};

#endif
