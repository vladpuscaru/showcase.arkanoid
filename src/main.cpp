//
// Created by Vlad Puscaru on 29.12.2023.
//

#include "./engine/GameEngine/GameEngine.h"
#include "./scenes/constants.h"
#include "./scenes/ScenePlay/ScenePlay.h"

int main() {

    GameEngine game(1080, 720, "Arkanoid", "../assets/assets.txt");

    std::shared_ptr<Scene> scenePlay = std::make_shared<ScenePlay>(&game, Scenes::PLAY, "../assets/levels/level1.txt");

    std::vector<std::shared_ptr<Scene>> sceneList {
        scenePlay
    };

    game.init(sceneList, 0);

    game.run();

    return 0;
}