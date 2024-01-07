//
// Created by Vlad Puscaru on 12.12.2023.
//

#ifndef COMP4300_ASSIGNMENT3_ANIMATION_H
#define COMP4300_ASSIGNMENT3_ANIMATION_H

#include <SFML/Graphics.hpp>
#include <cmath>

class Animation {
private:
    sf::Sprite m_sprite;
    int m_id;

    size_t m_frameCount; // Total number of Frames of Animation
    size_t m_currentFrame; // window frames since the animation is playing

    size_t m_speed; // The speed at which to play this animation
    sf::Vector2f m_size; // Size of an animation frame

public:
    Animation(int id, const sf::Texture& texture, size_t frameCount, size_t speed);

    void update();
    bool hasEnded() const;
    const sf::Vector2f& getSize();
    sf::Sprite& getSprite();
};


#endif //COMP4300_ASSIGNMENT3_ANIMATION_H
