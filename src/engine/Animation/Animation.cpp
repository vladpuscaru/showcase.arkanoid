//
// Created by Vlad Puscaru on 12.12.2023.
//

#include "Animation.h"

sf::Sprite &Animation::getSprite() {
    return m_sprite;
}

const sf::Vector2f &Animation::getSize() {
    return m_size;
}

Animation::Animation(int id, const sf::Texture &texture, size_t frameCount, size_t speed)
    : m_id(id)
    , m_sprite(texture)
    , m_frameCount(frameCount)
    , m_currentFrame(0)
    , m_speed(speed)
{
    m_size = sf::Vector2f ((float)texture.getSize().x / frameCount, (float)texture.getSize().y);
    m_sprite.setTextureRect(sf::IntRect(std::floor(m_currentFrame) * m_size.x, 0, m_size.x, m_size.y));
}

/**
 * Updates the animation to show the next frame, depending
 * on its speed
 * Animation loops when it reaches the end
 */
void Animation::update() {
    m_currentFrame++;

    int animFrame = (m_currentFrame / m_speed) % m_frameCount;

    sf::IntRect rectangle(animFrame * m_size.x, 0, m_size.x, m_size.y);
    m_sprite.setTextureRect(rectangle);
}

bool Animation::hasEnded() const {
    int animFrame = (m_currentFrame / m_speed);

    return animFrame > m_frameCount;
}
