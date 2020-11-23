#include "../include/SceneManager.h"

#include "../include/TitleScene.h"
#include "../include/SelectScene.h"
#include "../include/GameScene.h"
#include "../include/Game.h"

namespace gnGame {

    SceneManager::SceneManager()
        : sceneList()
        , sceneType(SceneType::Title)
        , fps()
    {
    }

    void SceneManager::initalize()
    {
        sceneList.emplace_back(ScenePtr(new TitleScene{ this }));
        sceneList.emplace_back(ScenePtr(new SelectScene{ this }));
        sceneList.emplace_back(ScenePtr(new GameScene{ this }));

        currentScene = sceneList[(int)sceneType];

        if (auto scene = currentScene.lock()) {
            scene.get()->onStart();
        }
    }

    void SceneManager::update()
    {
        fps.onUpdate();
        if (auto scene = currentScene.lock()) {
            scene.get()->onUpdate();
        }
        fps.drawFps();
        fps.wait();
    }

    void SceneManager::finalize()
    {
        if (auto scene = currentScene.lock()) {
            scene.get()->onFinal();
        }
    }

    void SceneManager::changeScene(SceneType _sceneType)
    {
        finalize();
        sceneType = _sceneType;

        switch (_sceneType)
        {
        case gnGame::SceneType::Title:
            currentScene = sceneList[(int)_sceneType];
            break;
        case gnGame::SceneType::Select:
            currentScene = sceneList[(int)_sceneType];
            break;
        case gnGame::SceneType::Game:
            currentScene = sceneList[(int)_sceneType];
            break;
        default:
            break;
        }

        if (auto scene = currentScene.lock()) {
            scene.get()->onStart();
        }
    }
}
