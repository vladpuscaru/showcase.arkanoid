//
// Created by Vlad Puscaru on 29.12.2023.
//

#ifndef ARKANOID_SCENEPLAY_H
#define ARKANOID_SCENEPLAY_H

#include "../../engine/GameEngine/GameEngine.h"
#include "../../engine/Scene/Scene.h"
#include "../constants.h"
#include "../../engine/Physics/Physics.h";

class ScenePlay : public Scene {
private:
    ConfigPlayer m_configPlayer;
    ConfigBall m_configBall;
    std::shared_ptr<Entity> m_player;
    std::shared_ptr<Entity> m_ball;
    sf::RectangleShape m_ballTrajectory;

    std::vector<ConfigTile> m_configTiles;

    sf::Text m_text;

    bool m_inPlay;

    sf::RectangleShape debugDraw; // TODO: remove this

    bool m_drawCollision;

    void spawnPlayer(bool killCurrent = false);
    void spawnBall(bool killCurrent = false);
    void spawnBullet();
    void spawnStartingTiles();
    void spawnTile(const ConfigTile& configTile, const sf::Vector2f& position);

    void loadConfigFromTextFile(const std::string& fileName);

    void releaseBall();
    void computeTrajectory(float angle);

    void sMovement();
    void sCollision();
    void sLifespan();
public:
    ScenePlay(GameEngine *game, int type, const std::string& configFile);

    void update() override;
    void sRender() override;
    void sDoAction(const Action &action) override;
};


#endif //ARKANOID_SCENEPLAY_H
