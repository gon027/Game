#include "../include/SelectScene.h"
#include "../include/SceneManager.h"

namespace gnGame {

	SelectScene::SelectScene(SceneManager* _sceneManager)
		: sceneManager(_sceneManager)
	{
	}

	void SelectScene::onStart()
	{
	}

	void SelectScene::onUpdate()
	{
		Debug::drawText(0, 0, "SelectScene");

		if (Input::getKeyDown(Key::Z)) {
			sceneManager->changeScene(SceneType::Game);
		}
	}

	void SelectScene::onFinal()
	{
	}

}
