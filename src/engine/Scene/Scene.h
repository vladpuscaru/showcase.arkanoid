//
// Created by Vlad Puscaru on 12.12.2023.
//

#ifndef COMP4300_ASSIGNMENT3_SCENE_H
#define COMP4300_ASSIGNMENT3_SCENE_H

#include <SFML/Graphics.hpp>
#include "../Entities/EntityManager/EntityManager.h"
#include "../Action/Action.h"

class GameEngine;

class Scene {
protected:
    GameEngine* m_game;
    EntityManager m_eManager;

    std::map<sf::Keyboard::Key, int> m_actionMap;

    int m_type;
    int m_currentFrame;
    bool m_paused;
    bool m_hasEnded;

public:
    Scene(GameEngine* game, int type);

    virtual void update() = 0;
    virtual void sRender() = 0;
    virtual void sDoAction(const Action& action) = 0;

    const std::map<sf::Keyboard::Key, int>& getActionMap() const;

    virtual void doAction(const Action& action);
    void simulate(int times);
    void registerAction(sf::Keyboard::Key key, int actionId);
    int getType();
};


#endif //COMP4300_ASSIGNMENT3_SCENE_H
