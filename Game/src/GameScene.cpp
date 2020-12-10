#include "../include/GameScene.h"
#include "../include/Global.h"
#include "../include/WindowInfo.h"
#include "../include/TextureManager.h"
#include "../include/EnemyManager.h"
#include "../include/BulletManager.h"
#include "../include/ItemManager.h"
#include "../include/EventManager.h"
#include "../include/SceneManager.h"
#include "../include/StageManager.h"
#include "../include/Camera.h"
#include "../include/Map.h"

namespace gnGame {

	GameScene::GameScene(SceneManager* _sceneManager)
		: sceneManager(_sceneManager)
		, mapStageList()
		, gameMap(new Map{ this })
		, player()
		, currentMapNumber(0)
	{
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
		gameMap->loadMapFile(global::MapAsset("TestMap_1"));
		Camera::setMapInfo(gameMap->getMapSize());

		player.onStart();
		player.setMap(gameMap);
		player.initPosition(gameMap->getStartPoint());
	}

	void GameScene::onUpdate()
	{

		if (Input::getKeyDown(Key::S)) {
			sceneManager->changeScene(SceneType::Title);
		}
		
		gameMap->drawMap();
		player.onUpdate();

		EnemyManager::getIns()->onUpdateEnemyList();
		EnemyManager::getIns()->collisionPlayer(player);

		BulletManager::getIns()->onUpdateBulletList();
		BulletManager::getIns()->collisionMap(*gameMap);
		BulletManager::getIns()->collisionActor(player);

		ItemManager::getIns()->onUpdateItemList();
		ItemManager::getIns()->collisionPlayer(player);

		EventManager::getIns()->collisionPlayer(player);
		EventManager::getIns()->onUpdateEventList();
	}

	void GameScene::onFinal()
	{
	}

	Player* GameScene::getPlayer()
	{
		return &player;
	}

	Map* GameScene::getMap()
	{
		return gameMap;
	}

	void GameScene::resetMap()
	{
		EnemyManager::getIns()->claerList();
		BulletManager::getIns()->claerList();
		ItemManager::getIns()->claerList();
		EventManager::getIns()->claerList();
	}

	void GameScene::nextMap()
	{
		// Managerのリストをすべて消去
		resetMap();

		// マップの数を1つ進める
		currentMapNumber = (currentMapNumber + 1) % 4;

		// マップをクリアする
		gameMap->claerMap();

		// マップを読み込む
		gameMap->loadMapFile(global::MapAsset(""));

		// カメラをマップに収める
		Camera::setMapInfo(gameMap->getMapSize());

		player.initPosition(gameMap->getStartPoint());
	}

}
