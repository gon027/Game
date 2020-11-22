#include "../include/TitleScene.h"
#include "../include/SceneManager.h"

namespace gnGame {

	TitleScene::TitleScene(SceneManager* _sceneManager)
		: sceneManager(_sceneManager)
	{
	}

	void TitleScene::onStart()
	{
	}

	void TitleScene::onUpdate()
	{
		Debug::drawText(0, 0, "TitleScene");

		if (Input::getKeyDown(Key::Z)) {
			sceneManager->changeScene(SceneType::Select);
		}
	}

	void TitleScene::onFinal()
	{
	}

}
