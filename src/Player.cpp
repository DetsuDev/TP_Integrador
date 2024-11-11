#include "Player.h"
#include "Projectile.h"

Player::Player()
{
    _texture.loadFromFile("assets/textures/player.png");
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2,0);
    _sprite.setPosition(320,256);
    health = 3;  // Inicializamos las vidas del jugador
}
void Player::update(float deltaTime)
{
    _speed = {0,0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) _speed.y = -4;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _speed.x = -4;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) _speed.y = 4;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _speed.x = 4;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) shoot(sf::Keyboard::Up);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) shoot(sf::Keyboard::Left);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) shoot(sf::Keyboard::Down);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) shoot(sf::Keyboard::Right);

    _sprite.move(_speed);

    if (_speed.x < 0) _sprite.setScale(-1, 1);
    else if (_speed.x > 0) _sprite.setScale(1, 1);

    if (_sprite.getGlobalBounds().left < 32)
        _sprite.setPosition(_sprite.getOrigin().x + 32, _sprite.getPosition().y);
    if (_sprite.getGlobalBounds().top < 48)
        _sprite.setPosition(_sprite.getPosition().x, _sprite.getOrigin().y + 48);
    if (_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > 608)
        _sprite.setPosition(608 - _sprite.getGlobalBounds().width + _sprite.getOrigin().x, _sprite.getPosition().y);
    if (_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height > 480)
        _sprite.setPosition(_sprite.getPosition().x, 480 - _sprite.getGlobalBounds().height + _sprite.getOrigin().y);


    // Aquí va la lógica de movimiento del jugador...

    // Actualiza cada proyectil y elimina los que salen de la pantalla
    for (size_t i = 0; i < projectiles.size(); ++i) {
        projectiles[i].update(deltaTime);
        if (projectiles[i].isOffScreen()) {
            projectiles.erase(projectiles.begin() + i);
            --i;
        }
    }
}

sf::Vector2f Player::getPosition() const {
    return _sprite.getPosition();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);// Dibuja cada proyectil
    for (size_t i = 0; i < projectiles.size(); ++i) {
        projectiles[i].render(target);  // Llamamos al método render de cada proyectil
    }
}

void Player::shoot(sf::Keyboard::Key _key) {
    // Disparo solo si ha pasado el intervalo de disparo
    if (shootCooldown.getElapsedTime().asSeconds() >= shootInterval) {
        // Dirección hacia arriba para el proyectil
        sf::Vector2f direction;
        if (_key == sf::Keyboard::Up) direction = sf::Vector2f(0, -1);
        if (_key == sf::Keyboard::Left) direction = sf::Vector2f(-1, 0);
        if (_key == sf::Keyboard::Down) direction = sf::Vector2f(0, 1);
        if (_key == sf::Keyboard::Right) direction = sf::Vector2f(1, 0);
        // Agregar el proyectil al vector de proyectiles
        projectiles.push_back(Projectile(_sprite.getPosition(), direction, projectileSpeed));
        shootCooldown.restart();
    }
}

std::vector<Projectile>& Player::getProjectiles() {
    return projectiles;
}
void Player::hurt()
{
    if (health > 0) {
        health--;  // Restar una vida
    }
}

int Player::getLifes() const
{
    return health;
}
sf::FloatRect Player::getBounds() const
{
    return _sprite.getGlobalBounds();
}




