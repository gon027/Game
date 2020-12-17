#include "../include/SelectScene.h"
#include "../include/WindowInfo.h"
#include "../include/SceneManager.h"
#include "../include/TextureManager.h"
#include "../include/StageManager.h"

namespace gnGame {

	namespace {
		constexpr auto HarfWindowWidth{ WindowInfo::WindowWidth / 2.0f };
		constexpr auto HarfWindowHeight{ WindowInfo::WindowHeight / 2.0f };
	}

	// ----- SelectSceneUI -----
	SelectSceneUI::SelectSceneUI()
		: backGround()
		, number()
		, frame()
		, textureRegion()
	{
		backGround.setTexture(TextureManager::getTexture("bg3"));
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

		frame.draw({ HarfWindowWidth, 32.0f + HarfWindowHeight }, { 3.0f, 3.0f }, 0.0f);

		for (int i{ 0 }; i < StageManager::MAXSTAGE; ++i) {
			float x{ HarfWindowWidth + 96.0f * static_cast<float>(i) + 
					(-96.0f) * StageManager::getIns()->getCurrentStage() };
			float y{ HarfWindowHeight + 32.0f };

			number.draw(textureRegion[i],
				{ x, y },
				{ 2.0f, 2.0f },
				0.0f
			);
		}

		stageSelect();
	}

	void SelectSceneUI::onFinal()
	{
	}

	void SelectSceneUI::stageSelect()
	{
		if (Input::getKeyDown(Key::RIGHT)) {
			StageManager::getIns()->incrementCurrentStage();
		}

		if (Input::getKeyDown(Key::LEFT)) {
			StageManager::getIns()->decrementCurrentStage();
		}
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
		//Debug::drawText(0, 0, "SelectScene");

		selectSceneUI.onUpdate();

		// ゲームシーンへ進む
		if (Input::getKeyDown(Key::Z)) {
			sceneManager->changeScene(SceneType::Game);
		}

		// タイトルシーンへ戻る
		if (Input::getKeyDown(Key::X)) {
			sceneManager->changeScene(SceneType::Title);
		}
	}

	void SelectScene::onFinal()
	{
		selectSceneUI.onFinal();
	}
}
