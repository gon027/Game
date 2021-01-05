#include "../include/TitleScene.h"
#include "../include/SceneManager.h"
#include "../include/TextureManager.h"
#include "../include/StageManager.h"
#include "../include/Global.h"

namespace gnGame {

	// -----TitleUI -----
	TitleUI::TitleUI()
		: backGround()
		, text(50, "SODA")
		, title(100, "SODA")
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

		text.drawText(185, 350, "Press Z Key", Color::Black);
		title.drawText(120, 100, "Title Text", Color::Green);
	}

	void TitleUI::onFinal()
	{
	}

	// ----- TitleScene -----
	TitleScene::TitleScene(SceneManager* _sceneManager)
		: sceneManager(_sceneManager)
		, titleUI()
		, titleBgm()
		, buttonSE()
	{
		titleBgm.load(global::AudioAsset("bgm.wav"));
		titleBgm.setVolume(-3000);
		buttonSE.load(global::AudioAsset("select02.wav"));
		buttonSE.setVolume(-3000);
	}

	void TitleScene::onStart()
	{
		titleUI.onStart();
		titleBgm.setPosition(0);
		titleBgm.play(PlayType::Loop);
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
		titleBgm.stop();
	}
}
