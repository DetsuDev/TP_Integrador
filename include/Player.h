#pragma once
#include <SFML\Graphics.hpp>


class Player: public sf::Drawable
{
    sf::Sprite _sprite;
    sf::Texture _texture;
    float _speed = 10;

public:
    Player();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

