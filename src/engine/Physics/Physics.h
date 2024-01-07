//
// Created by Vlad Puscaru on 12.12.2023.
//

#ifndef COMP4300_ASSIGNMENT3_PHYSICS_H
#define COMP4300_ASSIGNMENT3_PHYSICS_H

#include "../Entities/Entity/Entity.h"

class Physics {
public:
    static sf::Vector2f GetOverlap(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB);
    static sf::Vector2f GetPreiovusOverlap(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB);
};


#endif //COMP4300_ASSIGNMENT3_PHYSICS_H
