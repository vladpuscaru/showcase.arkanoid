//
// Created by Vlad Puscaru on 12.12.2023.
//

#include "Scene.h"

const std::map<sf::Keyboard::Key, int>& Scene::getActionMap() const {
    return m_actionMap;
}

void Scene::doAction(const Action &action) {
    sDoAction(action);
}

void Scene::simulate(int times) {
    for (int i = 0; i < times; i++) {
        update();
    }
}

void Scene::registerAction(sf::Keyboard::Key key, int actionId) {
    m_actionMap.insert(std::make_pair(key, actionId));
}

Scene::Scene(GameEngine* game, int type)
    : m_game(game), m_type(type)
{

}

int Scene::getType() {
    return m_type;
}
