#include "../include/SelectScene.h"
#include "../include/SceneManager.h"
#include "../include/TextureManager.h"

namespace gnGame {

	// ----- SelectSceneUI -----
	SelectSceneUI::SelectSceneUI()
		: backGround()
	{
		backGround.setTexture(TextureManager::getTexture("Back"));
	}

	SelectSceneUI::~SelectSceneUI()
	{
	}

	void SelectSceneUI::onStart()
	{
	}

	void SelectSceneUI::onUpdate()
	{
		backGround.draw(Vector2::Zero, Vector2::One, 0.0f, false);
	}

	void SelectSceneUI::onFinal()
	{
	}


	// ----- SelectScene -----
	SelectScene::SelectScene(SceneManager* _sceneManager)
		: sceneManager(_sceneManager)
		, selectSceneUI()
	{
	}

	void SelectScene::onStart()
	{
		selectSceneUI.onStart();
	}

	void SelectScene::onUpdate()
	{
		Debug::drawText(0, 0, "SelectScene");

		selectSceneUI.onUpdate();

		if (Input::getKeyDown(Key::Z)) {
			sceneManager->changeScene(SceneType::Game);
		}
	}

	void SelectScene::onFinal()
	{
		selectSceneUI.onFinal();
	}
}
