//
// Created by Vlad Puscaru on 12.12.2023.
//

#ifndef COMP4300_ASSIGNMENT3_COMPONENTS_H
#define COMP4300_ASSIGNMENT3_COMPONENTS_H

#include "../Animation/Animation.h"

class Component {
public:
    bool has = false;
};

class CTransform : public Component {
public:
    sf::Vector2f m_position;
    sf::Vector2f m_prevPosition;
    sf::Vector2f m_velocity;
    sf::Vector2f m_scale;
    double m_rotation;
    float m_speed;

    CTransform() = default;
    CTransform(sf::Vector2f position) : m_position(position), m_prevPosition(position), m_velocity({0, 0}) {}
    CTransform(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f scale, double rotation) : m_position(position), m_velocity(velocity), m_scale(scale), m_rotation(rotation) {}
};

class CBoundingBox : public Component {
public:
    sf::Vector2f m_size;
    sf::Vector2f m_halfSize;

    CBoundingBox() = default;
    explicit CBoundingBox(sf::Vector2f size) : m_size(size), m_halfSize(size.x / 2, size.y / 2) {}
};

class CInput : public Component {
public:
    bool isMovingRight = false;
    bool isMovingLeft = false;
    bool isJumping = false;
    bool isFiring = false;
};

class CScore : public Component {
public:
    int m_score;

    CScore() = default;
};

class CLifespan : public Component {
public:
    int m_originalLives = 1;
    int m_lives = 1;

    CLifespan() = default;
    explicit CLifespan(int lives) : m_originalLives(lives), m_lives(lives) {}
};

class CAnimation : public Component {
public:
    std::shared_ptr<Animation> m_animation;

    CAnimation() = default;
    CAnimation(std::shared_ptr<Animation> animation)
        : m_animation(animation)
    {}
};

#endif //COMP4300_ASSIGNMENT3_COMPONENTS_H
