#include "../include/GameScene.h"
#include "../include/TextureManager.h"
#include "../include/SceneManager.h"
#include "../include/CoinScoreManager.h"
#include "../include/StageManager.h"
#include "../include/ObjectManager.h"
#include "../include/ActorManager.h"
#include "CollisionManager.h"

#include "../include/ShotEnemy.h"
#include "../include/Bullet.h"
#include "../include/Boss.h"
#include "../include/NomalEnemy.h"
#include "../include/WalkEnemy.h"
#include "../include/Coin.h"

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
		, player(new Player{})
		, currentStageNumber(0)
		, stages()
	{

		// ステージの登録
#if _DEBUG
		// デバッグ用ステージ
		stages.emplace_back(new DebugStage{ gameMap, player });
#else
		// 本番ステージ
		stages.emplace_back(new TutorialStage{ gameMap, &player });
		stages.emplace_back(new Stage1{ gameMap, &player });
		stages.emplace_back(new Stage2{ gameMap, &player });
		stages.emplace_back(new BossStage{ gameMap, &player });
#endif // DEBUG
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
		player->onStart();
		player->setMap(gameMap);

		CollisionManager::getIns()->setPlayer(player);

		EnemyPtr e = EnemyPtr(new ShotEnemy{ this, {200, 200}, {20, 50, 2, 2, 2.0f}, Direction::Left });
		e->setMap(gameMap);
		e->onStart();
		ActorManager::getIns()->addActor(e);
		CollisionManager::getIns()->addActor(e);

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
		//if (!player->getActive()) {
			//player->respawn(gameMap->getStartPoint());
		//}
		ActorManager::getIns()->onUpdate();

		stages[currentStageNumber]->onUpdate();

		player->onUpdate();

		CollisionManager::getIns()->onUpdate();

		player->onDraw();
		ActorManager::getIns()->onDraw();
	}

	void GameScene::onFinal()
	{
		stages[currentStageNumber]->onFinal();
	}

	std::shared_ptr<Player>& GameScene::getPlayer()
	{
		return player;
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
		player->reset();
		sceneManager->changeScene(SceneType::Select);
	}

}