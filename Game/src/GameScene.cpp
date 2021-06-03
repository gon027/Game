#include "../include/GameScene.h"
#include "../include/TextureManager.h"
#include "../include/SceneManager.h"
#include "../include/CoinScoreManager.h"
#include "../include/StageManager.h"
#include "../include/BulletManager.h"

namespace gnGame {

	namespace Static {
		using MapStageList = std::vector<std::vector<std::string>>;
		static MapStageList mapStageList(4);     // マップステージのファイルリスト
	}

	GameSceneUI::GameSceneUI()
		: coinSprite()
		, scoreText(32, "SODA")
	{
		coinSprite.setTexture(TextureManager::getTexture("Coin"));
	}

	void GameSceneUI::onStart()
	{
	}

	void GameSceneUI::onUpdate()
	{
		coinSprite.draw({ 532.0f, 16.0f }, Vector2::One, 0.0f, false);

		auto scoreString = std::to_string(CoinScoreManager::getIns()->getScore());
		scoreText.drawText({ 575.0f, 17.0f }, scoreString, Color::White);
	}

	void GameSceneUI::onFinal()
	{
	}

	GameScene::GameScene(SceneManager* _sceneManager)
		: sceneManager(_sceneManager)
		, gameSceneUI()
		, gameMap(new Map{ this })
		, player()
		, currentStageNumber(0)
		, stages()
	{

		// ステージの登録
		stages.emplace_back(new TutorialStage{ gameMap, &player });
		stages.emplace_back(new Stage1{ gameMap, &player });
		stages.emplace_back(new Stage2{ gameMap, &player });
		stages.emplace_back(new BossStage{ gameMap, &player });
	}

	GameScene::~GameScene()
	{
		if (gameMap) {
			delete gameMap;
			gameMap = nullptr;
		}
	}

	void GameScene::onStart()
	{
		currentStageNumber = StageManager::getIns()->getCurrentStage();
		stages[currentStageNumber]->onStart();
	}

	void GameScene::onUpdate()
	{
#if _DEBUG
		// セレクトシーンへ戻る
		if (Input::getKeyDown(Key::A)) {
			sceneManager->changeScene(SceneType::Select);
		}

		// ステージを1進める
		if (Input::getKeyDown(Key::F)) {
			nextMap();
		}

#endif // DEBUG

		// プレイヤーが死亡した場合
		if (!player.getActive()) {
			player.respawn(gameMap->getStartPoint());
		}

		BulletManager::getIns()->collisionActor(player, this);

		stages[currentStageNumber]->onUpdate();
	}

	void GameScene::onFinal()
	{
		stages[currentStageNumber]->onFinal();
	}

	Player* GameScene::getPlayer() 
	{
		return &player;
	}

	Map* GameScene::getMap()
	{
		return gameMap;
	}

	void GameScene::nextMap()
	{
		stages[currentStageNumber]->nextMap();
	}

	void GameScene::changeSelectScene()
	{
		player.reset();
		sceneManager->changeScene(SceneType::Select);
	}

}