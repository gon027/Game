#include "../include/TitleScene.h"
#include "../include/SceneManager.h"
#include "../include/TextureManager.h"
#include "../include/StageManager.h"
#include "../include/Global.h"

namespace gnGame {

	// -----TitleUI -----
	TitleUI::TitleUI()
		: titleSprite()
		, backGround()
		, text(50, "SODA")
		, title(100, "SODA")
	{
		titleSprite.setTexture(TextureManager::getTexture("Title"));
		backGround.setTexture(TextureManager::getTexture("Title_BG"));
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
		titleSprite.draw({ 200.0f, 200.0f }, Vector2::One, 0.0f, false);

		text.drawText(185, 350, "Press Z Key", Color::Black);
		//title.drawText(120, 100, "Title Text", Color::Green);
	}

	void TitleUI::onFinal()
	{
	}

	// ----- TitleScene -----
	TitleScene::TitleScene(SceneManager* _sceneManager)
		: sceneManager(_sceneManager)
		, titleUI()
		, buttonSE()
	{
		buttonSE.load(global::AudioAsset("se_select.wav"));
		buttonSE.setVolume(-3000);
	}

	void TitleScene::onStart()
	{
		titleUI.onStart();
	}

	void TitleScene::onUpdate()
	{
		titleUI.onUpdate();

		if (Input::getKeyDown(Key::Z)) {
			buttonSE.play();
			sceneManager->changeScene(SceneType::Select);
		}
	}

	void TitleScene::onFinal()
	{
		titleUI.onFinal();
	}
}
