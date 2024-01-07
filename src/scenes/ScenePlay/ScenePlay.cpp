//
// Created by Vlad Puscaru on 29.12.2023.
//

#include "ScenePlay.h"

ScenePlay::ScenePlay(GameEngine *game, int type, const std::string &configFile) : Scene(game, type) {
    loadConfigFromTextFile(configFile);
    spawnPlayer();
    spawnBall();
    spawnStartingTiles();

    registerAction(sf::Keyboard::A, Actions::MOVE_LEFT);
    registerAction(sf::Keyboard::D, Actions::MOVE_RIGHT);
    registerAction(sf::Keyboard::Left, Actions::ROTATE_LEFT);
    registerAction(sf::Keyboard::Right, Actions::ROTATE_RIGHT);
    registerAction(sf::Keyboard::Space, Actions::SHOOT);

    registerAction(sf::Keyboard::C, Actions::TOGGLE_COLLISIONS);
    registerAction(sf::Keyboard::Q, Actions::QUIT);

    m_text.setFont(m_game->getAssets().getFont(Fonts::MAIN_FONT));
    m_text.setCharacterSize(32);
    m_text.setFillColor(sf::Color::White);

    m_inPlay = false;
}

void ScenePlay::update() {
    m_eManager.update();

    sLifespan();
    sMovement();
    sCollision();
    sRender();
}

void ScenePlay::sRender() {
    auto &w = m_game->getWindow();
    w.clear(sf::Color::Black);

    for (auto &e: m_eManager.getEntities()) {
        if (!e->hasComponent<CTransform>()) {
            continue;
        }
        auto &t = e->getComponent<CTransform>();

        if (m_drawCollision) {
            if (!e->hasComponent<CBoundingBox>()) {
                continue;
            }
            auto &b = e->getComponent<CBoundingBox>();

            sf::RectangleShape rect;
            rect.setSize(b.m_size);
            rect.setFillColor(sf::Color::Transparent);
            rect.setOutlineColor(sf::Color::Green);
            rect.setOutlineThickness(1.f);
            rect.setPosition(t.m_position);

            w.draw(rect);
        }
    }

    if (!m_inPlay) {
        w.draw(m_ballTrajectory);
    }

    if (m_player->hasComponent<CScore>()) {
        m_text.setString("Score: " + std::to_string(m_player->getComponent<CScore>().m_score));
        m_text.setPosition({ 15.0f, 35.0f });
        w.draw(m_text);
    }

    if (m_player->hasComponent<CLifespan>()) {
        m_text.setString("Lives: " + std::to_string(m_player->getComponent<CLifespan>().m_lives));
        m_text.setPosition({ m_game->getWindow().getSize().x - m_text.getLocalBounds().getSize().x - 35.0f, 35.0f });
        w.draw(m_text);
    }

    w.draw(debugDraw); // TODO: Remove this

    w.display();
}

void ScenePlay::sDoAction(const Action &action) {
    if (action.getType() == Action::ActionTypes::START) {
        switch (action.getId()) {
            case Actions::TOGGLE_COLLISIONS:
                m_drawCollision = !m_drawCollision;
                break;
            case Actions::QUIT:
                // TODO: Back to menu
                m_game->quit();
                break;
            case Actions::MOVE_LEFT:
                m_player->getComponent<CInput>().isMovingLeft = true;
                break;
            case Actions::MOVE_RIGHT:
                m_player->getComponent<CInput>().isMovingRight = true;
                break;
            case Actions::ROTATE_LEFT:
                computeTrajectory(m_ballTrajectory.getRotation() - 10.f);
                break;
            case Actions::ROTATE_RIGHT:
                computeTrajectory(m_ballTrajectory.getRotation() + 10.f);
                break;
            case Actions::SHOOT:
                if (m_inPlay) {
                    spawnBullet();
                } else {
                    releaseBall();
                }
                break;
        }
    }

    if (action.getType() == Action::ActionTypes::STOP) {
        switch (action.getId()) {
            case Actions::MOVE_LEFT:
                m_player->getComponent<CInput>().isMovingLeft = false;
                break;
            case Actions::MOVE_RIGHT:
                m_player->getComponent<CInput>().isMovingRight = false;
                break;
        }
    }
}

void ScenePlay::spawnPlayer(bool killCurrent) {
    int lives = 3;
    int score = 0;

    if (killCurrent && m_player) {
        if (m_player->hasComponent<CLifespan>()) {
            lives = m_player->getComponent<CLifespan>().m_lives;
        }
        if (m_player->hasComponent<CScore>()) {
            score = m_player->getComponent<CScore>().m_score;
        }
        m_player->destroy();
    }

    // TODO: Add Animation Component
    m_player = m_eManager.addEntity(Entities::PLAYER);
    m_player->addComponent<CTransform>(
            sf::Vector2f{m_game->getWindow().getSize().x / 2.f - m_configPlayer.bbWidth / 2,
                         m_game->getWindow().getSize().y - 150.f}
    );
    m_player->getComponent<CTransform>().m_speed = m_configPlayer.speed;

    m_player->addComponent<CBoundingBox>(
            sf::Vector2f{m_configPlayer.bbWidth, m_configPlayer.bbHeight}
    );

    m_player->addComponent<CInput>();

    m_player->addComponent<CScore>();
    m_player->getComponent<CScore>().m_score = score;

    m_player->addComponent<CLifespan>(lives);
}

void ScenePlay::spawnBall(bool killCurrent) {
    m_inPlay = false;

    if (killCurrent && m_ball) {
        m_ball->destroy();
    }

    // TODO: Add Animation Component
    m_ball = m_eManager.addEntity(Entities::BALL);
    m_ball->addComponent<CTransform>(
            sf::Vector2f{
                    m_player->getComponent<CTransform>().m_position.x +
                    m_player->getComponent<CBoundingBox>().m_halfSize.x - m_configBall.bbWidth / 2,
                    m_player->getComponent<CTransform>().m_position.y - 20.f}
    );
    m_ball->getComponent<CTransform>().m_speed = m_configBall.speed;

    m_ball->addComponent<CBoundingBox>(
            sf::Vector2f{m_configBall.bbWidth, m_configBall.bbHeight}
    );

    auto &bT = m_ball->getComponent<CTransform>();
    auto &bB = m_ball->getComponent<CBoundingBox>();


    m_ballTrajectory.setSize({bT.m_position.y, 1.f});
    m_ballTrajectory.setFillColor(sf::Color::Blue);
    m_ballTrajectory.setPosition({
                                         bT.m_position.x + bB.m_halfSize.x,
                                         bT.m_position.y - m_ballTrajectory.getSize().y
                                 });
    m_ballTrajectory.setRotation(-90); // start rotation
}

void ScenePlay::loadConfigFromTextFile(const std::string &fileName) {
    FileContent levelConfig = m_game->splitFileContent(fileName);

    for (const std::vector<std::string> &line: levelConfig) {
        if (line[0] == "Player") {
            m_configPlayer.bbWidth = std::atof(line[1].c_str());
            m_configPlayer.bbHeight = std::atof(line[2].c_str());
            m_configPlayer.speed = std::atof(line[3].c_str());
        }

        if (line[0] == "Ball") {
            m_configBall.bbWidth = std::atof(line[1].c_str());
            m_configBall.bbHeight = std::atof(line[2].c_str());
            m_configBall.speed = std::atof(line[3].c_str());
        }

        if (line[0] == "Tile") {
            ConfigTile configTile;
            configTile.bbWidth = std::atof(line[1].c_str());
            configTile.bbHeight = std::atof(line[2].c_str());
            configTile.lifespan = std::atoi(line[3].c_str());

            m_configTiles.emplace_back(configTile);
        }
    }
}

void ScenePlay::sMovement() {
    if (!m_inPlay) {
        if (m_player->getComponent<CTransform>().m_velocity.x != 0) {
            m_ball->getComponent<CTransform>().m_velocity = m_player->getComponent<CTransform>().m_velocity;
            m_ballTrajectory.move(m_player->getComponent<CTransform>().m_velocity);
        } else {
            m_ball->getComponent<CTransform>().m_velocity = {0, 0};
        }
    }

    for (auto &e: m_eManager.getEntities()) {
        if (!e->hasComponent<CTransform>()) {
            continue;
        }
        auto &tr = e->getComponent<CTransform>();

        if (e->hasComponent<CInput>()) {
            auto &in = e->getComponent<CInput>();
            if (in.isMovingLeft) {
                tr.m_velocity.x = -tr.m_speed;
            } else if (in.isMovingRight) {
                tr.m_velocity.x = +tr.m_speed;
            } else {
                tr.m_velocity.x = 0.0f;
            }
        }

        tr.m_prevPosition = tr.m_position;
        tr.m_position += tr.m_velocity;
    }
}

void ScenePlay::sCollision() {
    // Ball Collisions with screen
    auto &ballTr = m_ball->getComponent<CTransform>();
    auto &ballBb = m_ball->getComponent<CBoundingBox>();

    float ballTop = ballTr.m_position.y;
    float ballRight = ballTr.m_position.x + ballBb.m_size.x;
    float ballBottom = ballTr.m_position.y + ballBb.m_size.y;
    float ballLeft = ballTr.m_position.x;

    if (ballTop <= 0) {
        // Ball hit top of the screen
        ballTr.m_position.y = 0;
        ballTr.m_velocity.y = -ballTr.m_velocity.y;
    }

    if (ballRight >= m_game->getWindow().getSize().x) {
        // Ball hit right of the screen
        ballTr.m_position.x = m_game->getWindow().getSize().x - ballBb.m_size.x;
        ballTr.m_velocity.x = -ballTr.m_velocity.x;
    }

    if (ballBottom >= m_game->getWindow().getSize().y) {
        // Ball hit bottom of the screen
        m_player->getComponent<CLifespan>().m_lives--;
        spawnPlayer(true);
        spawnBall();
    }

    if (ballLeft <= 0) {
        // Ball hit left of the screen
        ballTr.m_position.x = 0;
        ballTr.m_velocity.x = -ballTr.m_velocity.x;
    }

    // Player Collisions with screen
    auto &playerTr = m_player->getComponent<CTransform>();
    auto &playerBb = m_player->getComponent<CBoundingBox>();

    float playerRight = playerTr.m_position.x + playerBb.m_size.x;
    float playerLeft = playerTr.m_position.x;

    if (playerLeft <= 0) {
        playerTr.m_position.x = 0;
        playerTr.m_velocity.x = 0;
    }

    if (playerRight >= m_game->getWindow().getSize().x) {
        playerTr.m_position.x = m_game->getWindow().getSize().x - playerBb.m_size.x;
        playerTr.m_velocity.x = 0;
    }

    // Player - Ball Collisions
    sf::Vector2f overlap = Physics::GetOverlap(m_ball, m_player);
    if (overlap.x > 0 && overlap.y > 0) {
        ballTr.m_position.y = playerTr.m_position.y - ballBb.m_size.y;
        ballTr.m_velocity.y = -ballTr.m_velocity.y;
    }

    // Tile - Ball Collisions
    for (auto &e: m_eManager.getEntities(Entities::TILE)) {
        overlap = Physics::GetOverlap(m_ball, e);
        if (overlap.x > 0 && overlap.y > 0) {
            if (e->hasComponent<CLifespan>()) {
                e->getComponent<CLifespan>().m_lives--;
            }

            sf::Vector2f previousOverlap = Physics::GetPreiovusOverlap(m_ball, e);
            if (previousOverlap.x > 0) {
                if (m_ball->getComponent<CTransform>().m_velocity.y > 0) {
                    // Coming from top
                    m_ball->getComponent<CTransform>().m_position.y -= overlap.y;
                } else {
                    // Coming from bottom
                    m_ball->getComponent<CTransform>().m_position.y += overlap.y;
                }
                m_ball->getComponent<CTransform>().m_velocity.y = -m_ball->getComponent<CTransform>().m_velocity.y;
            } else if (previousOverlap.y > 0) {
                if (m_ball->getComponent<CTransform>().m_velocity.x > 0) {
                    // Coming from left
                    m_ball->getComponent<CTransform>().m_position.x -= overlap.x;
                } else {
                    // Coming from right
                    m_ball->getComponent<CTransform>().m_position.x += overlap.x;
                }
                m_ball->getComponent<CTransform>().m_velocity.x = -m_ball->getComponent<CTransform>().m_velocity.x;
            } else {
                // Tricky, coming from diagonal
                // TODO: Decide on this case
            }
        }
    }

}

void ScenePlay::releaseBall() {
    sf::Vector2f direction = { 1.0f, 0.0f };
    float theta = (M_PI / 180) * (m_ballTrajectory.getRotation());
    float newX = std::cos(theta) * direction.x - std::sin(theta) * direction.y;
    float newY = std::sin(theta) * direction.x + std::cos(theta) * direction.y;
    direction = { newX, newY };

    m_ball->getComponent<CTransform>().m_velocity = direction * m_ball->getComponent<CTransform>().m_speed;
    m_inPlay = true;
}

void ScenePlay::computeTrajectory(float angle) {
    // TODO: Compute a more complex trajectory (multiple lines)
    m_ballTrajectory.setRotation(angle);
}

void ScenePlay::spawnBullet() {

}

void ScenePlay::spawnTile(const ConfigTile &configTile, const sf::Vector2f &position) {
    // TODO: Add Animation Component
    auto tile = m_eManager.addEntity(Entities::TILE);
    tile->addComponent<CTransform>(position);
    tile->addComponent<CBoundingBox>(sf::Vector2f{configTile.bbWidth, configTile.bbHeight});
    tile->addComponent<CLifespan>();
}

void ScenePlay::spawnStartingTiles() {
    float paddingX = 25;
    float paddingY = 105;
    float x = paddingX;
    float y = paddingY;

    float maxRowHeight = paddingY;

    for (auto configTile: m_configTiles) {
        if (x + configTile.bbWidth > m_game->getWindow().getSize().x - paddingX) {
            x = paddingX;
            y += maxRowHeight;
        }

        spawnTile(configTile, {x, y});

        x += configTile.bbWidth + paddingX;
        maxRowHeight = (y + configTile.bbHeight - y > maxRowHeight) ? y + configTile.bbHeight - y : maxRowHeight;
    }
}

void ScenePlay::sLifespan() {
    for (auto &e: m_eManager.getEntities()) {
        if (!e->hasComponent<CLifespan>()) {
            continue;
        }

        if (e->getComponent<CLifespan>().m_lives <= 0) {
            e->destroy();
            if (m_player->hasComponent<CScore>()) {
                m_player->getComponent<CScore>().m_score += 10 * e->getComponent<CLifespan>().m_originalLives;
            }
        }
    }
}


