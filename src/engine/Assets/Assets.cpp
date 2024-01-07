//
// Created by Vlad Puscaru on 12.12.2023.
//

#include "Assets.h"

const sf::Texture &Assets::getTexture(int id) const {
    assert(m_textures.find(id) != m_textures.end());
    return m_textures.find(id)->second;
}

const std::shared_ptr<Animation> &Assets::getAnimation(int id) const {
    assert(m_animations.find(id) != m_animations.end());
    return m_animations.find(id)->second;
}

const sf::Sound &Assets::getSound(int id) const {
    assert(m_sounds.find(id) != m_sounds.end());
    return m_sounds.find(id)->second;
}

const sf::Font &Assets::getFont(int id) const {
    assert(m_fonts.find(id) != m_fonts.end());
    return m_fonts.find(id)->second;
}

void Assets::addTexture(int id, const std::string &path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        std::cerr << "Error loading texture from " << path << std::endl;
        exit(-1);
    }
    m_textures[id] = texture;
}

void Assets::addAnimation(int id, const Animation &animation) {
    m_animations[id] = std::make_shared<Animation>(animation);
}

void Assets::addSound(int id, const std::string &path) {
    sf::SoundBuffer soundBuffer;
    if (!soundBuffer.loadFromFile(path)) {
        std::cerr << "Error loading sound from " << path << std::endl;
        exit(-1);
    }
    m_sounds[id] = sf::Sound(soundBuffer);
}

void Assets::addFont(int id, const std::string &path) {
    sf::Font font;
    if (!font.loadFromFile(path)) {
        std::cerr << "Error loading font from " << path << std::endl;
        exit(-1);
    }
    m_fonts[id] = font;
}
