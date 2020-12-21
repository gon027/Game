#include "../include/TitleScene.h"
#include "../include/SceneManager.h"
#include "../include/TextureManager.h"
#include "../include/StageManager.h"

namespace gnGame {

	// -----TitleUI -----
	TitleUI::TitleUI()
		: backGround()
		, font(50, "SODA")
	{
		backGround.setTexture(TextureManager::getTexture("bg2"));
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

		font.drawText(185, 350, "Press Z Key", Color::Black);
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
