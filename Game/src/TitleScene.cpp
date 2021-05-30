#include "../include/TitleScene.h"
#include "../include/SceneManager.h"
#include "../include/TextureManager.h"
#include "../include/StageManager.h"
#include "../include/AudioManager.h"
#include "../include/Global.h"

namespace gnGame {

	// -----TitleUI -----
	TitleUI::TitleUI()
		: titleSprite()
		, backGround()
		, text(50, "SODA")
		, titleText(110, "SODA")
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
		//titleSprite.draw({ 125.0f, 90.0f }, Vector2::One, 0.0f, false);

		text.drawText(185, 350, "Press Z Key", Color::Black);
		titleText.drawText(75, 100, "Pico Action", Color::Green);
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
			AudioManager::getIns()->play("SE_select");
			sceneManager->changeScene(SceneType::Select);
		}
	}

	void TitleScene::onFinal()
	{
		titleUI.onFinal();
	}
}
