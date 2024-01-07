//
// Created by Vlad Puscaru on 12.12.2023.
//

#include "Physics.h"

// positive overlap in both dimensions means there is a collision
sf::Vector2f Physics::GetOverlap(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB) {
    // TODO: Return the overlap rectangle size of the bounding boxes

    auto& bA = entityA->getComponent<CBoundingBox>();
    auto& tA = entityA->getComponent<CTransform>();

    auto& bB = entityB->getComponent<CBoundingBox>();
    auto& tB = entityB->getComponent<CTransform>();

    sf::Vector2f centerA = tA.m_position + bA.m_halfSize;
    sf::Vector2f centerB = tB.m_position + bB.m_halfSize;

    sf::Vector2f delta = {
            std::abs(centerB.x - centerA.x),
            std::abs(centerB.y - centerA.y)
    };

    return bB.m_halfSize + bA.m_halfSize - delta;
}

sf::Vector2f Physics::GetPreiovusOverlap(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB) {
    // TODO: Return the previous overlap rectangle size of the bounding boxes
    // Previous overlap uses the entity's previous position


    auto& bA = entityA->getComponent<CBoundingBox>();
    auto& tA = entityA->getComponent<CTransform>();

    auto& bB = entityB->getComponent<CBoundingBox>();
    auto& tB = entityB->getComponent<CTransform>();

    sf::Vector2f centerA = tA.m_prevPosition + bA.m_halfSize;
    sf::Vector2f centerB = tB.m_prevPosition + bB.m_halfSize;

    sf::Vector2f delta = {
            std::abs(centerB.x - centerA.x),
            std::abs(centerB.y - centerA.y)
    };

    return bB.m_halfSize + bA.m_halfSize - delta;
}
