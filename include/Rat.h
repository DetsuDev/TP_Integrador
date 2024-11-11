#ifndef RAT_H
#define RAT_H

#include "Enemy.h"  // Incluir Enemy para la herencia

class Rat : public Enemy
{
public:
    Rat();
    void update(Player& player);  // Si quieres sobrescribir update en Rat
    void respawn();
};

#endif // RAT_H
