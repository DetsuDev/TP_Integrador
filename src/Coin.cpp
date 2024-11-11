#include "Coin.h"

Coin::Coin()
{
    _texture.loadFromFile("assets/textures/coin.png");
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2,_sprite.getGlobalBounds().height/2);
}

void Coin::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

void Coin::respawn()
{// x y
    _sprite.setPosition(std::rand()%400 + _sprite.getGlobalBounds().width, std::rand()%400 + _sprite.getGlobalBounds().height);
}

sf::FloatRect Coin::getBounds() const
{
    return _sprite.getGlobalBounds();
}
