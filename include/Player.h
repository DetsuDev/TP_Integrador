#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Collisionable.h"
#include "Projectile.h"

class Player : public sf::Drawable, public Collisionable
{
    private:
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::Vector2f _speed;


    std::vector<Projectile> projectiles;
    sf::Clock shootCooldown;
    float projectileSpeed = 400.0f;
    float shootInterval = 0.5f;
    int health;
public:
    Player();
    void hurt();  // Método para recibir daño y restar vidas
    int getLifes() const;  // Obtener el número de vidas
    void update(float deltaTime);
    void shoot(sf::Keyboard::Key _key);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Keyboard::Key _key;
    std::vector<Projectile>& getProjectiles();
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;

};

