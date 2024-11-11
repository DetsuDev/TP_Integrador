#include "Projectile.h"

Projectile::Projectile(sf::Vector2f position, sf::Vector2f direction, float speed) {
    shape.setRadius(5.0f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
    velocity = direction * speed;
}

void Projectile::update(float deltaTime) {
    shape.move(velocity * deltaTime);
}

void Projectile::render(sf::RenderTarget& target) const {
    target.draw(shape);
}

bool Projectile::isOffScreen() const {
    return shape.getPosition().y < 0 || shape.getPosition().y > 600 ||
           shape.getPosition().x < 0 || shape.getPosition().x > 800;
}
sf::FloatRect Projectile::getBounds() const
{
    return shape.getGlobalBounds();
}
