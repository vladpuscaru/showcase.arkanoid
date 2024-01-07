//
// Created by Vlad Puscaru on 12.12.2023.
//

#ifndef COMP4300_ASSIGNMENT3_ASSETS_H
#define COMP4300_ASSIGNMENT3_ASSETS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Animation/Animation.h"

class Assets {
private:
    std::map<int, sf::Texture> m_textures;
    std::map<int, std::shared_ptr<Animation>> m_animations;
    std::map<int, sf::Sound> m_sounds;
    std::map<int, sf::Font> m_fonts;

public:
    void addTexture(int id, const std::string& path);
    void addAnimation(int id, const Animation& animation);
    void addSound(int id, const std::string& path);
    void addFont(int id, const std::string& path);

    const sf::Texture& getTexture(int id) const;
    const std::shared_ptr<Animation>& getAnimation(int id) const;
    const sf::Sound& getSound(int id) const;
    const sf::Font& getFont(int id) const;
};


#endif //COMP4300_ASSIGNMENT3_ASSETS_H
