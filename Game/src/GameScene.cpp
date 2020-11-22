#include "../include/GameScene.h"
#include "../include/SceneManager.h"

namespace gnGame {

	GameScene::GameScene(SceneManager* _sceneManager)
		: sceneManager(_sceneManager)
	{
	}

	void GameScene::onStart()
	{
	}

	void GameScene::onUpdate()
	{
		Debug::drawText(0, 0, "GameScene");

		if (Input::getKeyDown(Key::Z)) {
			sceneManager->changeScene(SceneType::Title);
		}
	}

	void GameScene::onFinal()
	{
	}

}
