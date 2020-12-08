#include "../include/SelectScene.h"
#include "../include/WindowInfo.h"
#include "../include/SceneManager.h"
#include "../include/TextureManager.h"

namespace gnGame {

	namespace {

	}

	// ----- SelectSceneUI -----
	SelectSceneUI::SelectSceneUI()
		: backGround()
		, number()
		, frame()
		, textureRegion()
		, stageNumber(0)
	{
		backGround.setTexture(TextureManager::getTexture("Back"));
		number.setTexture(TextureManager::getTexture("Number"));
		frame.setTexture(TextureManager::getTexture("UIFrame"));
		textureRegion = Texture::spriteTexture(TextureManager::getTexture("Number"), 3, 4);
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
		
		frame.draw({ WindowInfo::WindowWidth / 2.0f, 32 + WindowInfo::WindowHeight / 2.0f }, { 3.0f, 3.0f }, 0.0f);

		// Todo: 画像クラスを使いやすくする
		// 2倍にしたら原点にするには(48, 64)にする

		for (int i{ 0 }; i < 5; ++i) {
			float x = -32.0f + 48.0f + WindowInfo::WindowWidth / 2.0f + 96 * static_cast<float>(i) + (-96.0f) * stageNumber;
			float y = 64.0f + WindowInfo::WindowHeight / 2.0f;

			number.draw(textureRegion[i],
				{ x, y },
				{ 2.0f, 2.0f },
				0.0f,
				false
			);
		}

		if (Input::getKeyDown(Key::RIGHT)) {
			++stageNumber;
			if (stageNumber > 4) {
				stageNumber = 4;
			}
		}

		if (Input::getKeyDown(Key::LEFT)) {
			--stageNumber;
			if (stageNumber < 0) {
				stageNumber = 0;
			}
		}
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
