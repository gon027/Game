#include "../include/SelectScene.h"
#include "../include/WindowInfo.h"
#include "../include/SceneManager.h"
#include "../include/TextureManager.h"
#include "../include/StageManager.h"
#include "../include/Global.h"

namespace gnGame {

	// ステージの名前と座標の構造体
	struct StageName {
		Vector2 pos;     // 座標
		string stage;    // ステージの名前
	};

	namespace Static {
		constexpr auto HarfWindowWidth{ WindowInfo::WindowWidth / 2.0f };
		constexpr auto HarfWindowHeight{ WindowInfo::WindowHeight / 2.0f };

		static vector<StageName> stageName{
			{{210, 100}, "Tutorial" },
			{{230, 100}, "Stage1" },
			{{230, 100}, "Stage2" },
			{{230, 100}, "Stage3" },
			{{190, 100}, "BossStage" },
		};
	}

	// ----- SelectSceneUI -----
	SelectSceneUI::SelectSceneUI()
		: backGround()
		, number()
		, frame()
		, textureRegion()
		, text(30, "SODA")
		, stageNameFont(70, "SODA")
		, selectSE()
	{
		backGround.setTexture(TextureManager::getTexture("bg3"));
		number.setTexture(TextureManager::getTexture("Number"));
		frame.setTexture(TextureManager::getTexture("UIFrame"));
		textureRegion = Texture::spriteTexture(TextureManager::getTexture("Number"), 3, 4);
		selectSE.load(global::AudioAsset("select02.wav"));
		selectSE.setVolume(-4000);
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
		
		frame.draw({ Static::HarfWindowWidth, 32.0f + Static::HarfWindowHeight }, { 3.0f, 3.0f }, 0.0f);
		
		int currentStage = StageManager::getIns()->getCurrentStage();
		for (int i{ 0 }; i < StageManager::MAXSTAGE; ++i) {
			float x{ Static::HarfWindowWidth + 96.0f * static_cast<float>(i) + (-96.0f) * currentStage };
			float y{ Static::HarfWindowHeight + 32.0f };

			number.draw(textureRegion[i],
				{ x, y },
				{ 2.0f, 2.0f },
				0.0f
			);
		}

		/*
		// デバッグ
		if (Input::getKeyDown(Key::F)) {
			StageManager::getIns()->unlockStage();
		}
		*/
		
		auto& currentStageName = Static::stageName[currentStage];
		stageNameFont.drawText(currentStageName.pos, currentStageName.stage, Color::Black);
		text.drawText(10, 440, "Z Key : Next, X Key : Title", Color::Black);

		stageSelect();
	}

	void SelectSceneUI::onFinal()
	{
	}

	void SelectSceneUI::stageSelect()
	{
		if (Input::getKeyDown(Key::RIGHT)) {
			selectSE.stop();
			selectSE.play();
			StageManager::getIns()->incrementCurrentStage();
		}

		if (Input::getKeyDown(Key::LEFT)) {
			selectSE.stop();
			selectSE.play();
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
