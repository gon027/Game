#include "../include/TitleScene.h"
#include "../include/SceneManager.h"
#include "../include/TextureManager.h"

namespace gnGame {

	// -----TitleUI -----
	TitleUI::TitleUI()
		: backGround()
	{
		backGround.setTexture(TextureManager::getTexture("Back"));
	}

	TitleUI::~TitleUI()
	{
	}

	void TitleUI::onStart()
	{
	}

	void TitleUI::onUpdate()
	{
		backGround.draw(Vector2::Zero, Vector2::One, 0.0f, false);
	}

	void TitleUI::onFinal()
	{
	}

	// ----- TitleScene -----
	TitleScene::TitleScene(SceneManager* _sceneManager)
		: sceneManager(_sceneManager)
		, titleUI()
	{
	}

	void TitleScene::onStart()
	{
		titleUI.onStart();
	}

	void TitleScene::onUpdate()
	{
		Debug::drawText(0, 0, "TitleScene");

		titleUI.onUpdate();

		if (Input::getKeyDown(Key::Z)) {
			sceneManager->changeScene(SceneType::Select);
		}
	}

	void TitleScene::onFinal()
	{
		titleUI.onFinal();
	}
}
