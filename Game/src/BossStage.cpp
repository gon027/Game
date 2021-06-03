#include "../include/Stage.h"
#include "../include/Global.h"
#include "../include/TextureManager.h"
#include "../include/EnemyManager.h"
#include "../include/BulletManager.h"
#include "../include/ItemManager.h"
#include "../include/EventManager.h"
#include "../include/SceneManager.h"
#include "../include/StageManager.h"
#include "../include/AudioManager.h"
#include "../include/UIDrawer.h"
#include "../include/Camera.h"
#include "../include/Map.h"
#include "../TutorialObject.h"
#include "../include/Player.h"

namespace gnGame {

	BossStage::BossStage(Map* _map, Player* _player)
		: mapNameList()
		, backGround()
		, gameMap(_map)
		, player(_player)
		, currentMapNumber()
	{
		backGround.setTexture(1);

		mapNameList.push_back("BossStage/Stage_1");
		mapNameList.push_back("BossStage/Stage_2");
		mapNameList.push_back("BossStage/Clear");
	}

	void BossStage::onStart()
	{
		initMap();

		AudioManager::getIns()->play("BGM_game", PlayType::Loop);
	}

	void BossStage::onUpdate()
	{
		// 背景の描画
		backGround.draw();

		gameMap->drawMap();

		player->onUpdate();

		EnemyManager::getIns()->onUpdateEnemyList();
		EnemyManager::getIns()->collisionPlayer(*player);

		BulletManager::getIns()->onUpdateBulletList();
		BulletManager::getIns()->collisionMap(*gameMap);

		ItemManager::getIns()->onUpdateItemList();
		ItemManager::getIns()->collisionPlayer(*player);

		EventManager::getIns()->collisionPlayer(*player);
		EventManager::getIns()->onUpdateEventList();

		UIDrawer::getIns()->OndrawUIList();

	}

	void BossStage::onFinal()
	{
		AudioManager::getIns()->stop("BGM_game");
		AudioManager::getIns()->setPosition("BGM_game", 0);

		resetMap();
	}

	void BossStage::initMap()
	{
		// 現在のマップ番号を0にする
		currentMapNumber = 0;

		// マップをクリアする
		gameMap->claerMap();

		// マップを読み込む
		auto mapFile = global::MapAsset(mapNameList[currentMapNumber]);
		gameMap->loadMapFile(mapFile);

		// カメラをマップに収める
		Camera::setMapInfo(gameMap->getMapSize());

		// プレイヤーの位置設定
		player->onStart();
		player->setMap(gameMap);
		player->initPosition(gameMap->getStartPoint());
		Camera::setTarget(player->transform.pos);
	}

	void BossStage::nextMap()
	{
		player->setIsMove(false);

		// Managerのリストをすべて消去
		resetMap();

		// マップの数を1つ進める
		currentMapNumber = (currentMapNumber + 1) % 4;

		// マップをクリアする
		gameMap->claerMap();

		// マップを読み込む
		auto mapFile = global::MapAsset(mapNameList[currentMapNumber]);
		gameMap->loadMapFile(mapFile);

		// カメラをマップに収める
		Camera::setMapInfo(gameMap->getMapSize());

		// プレイヤーの位置設定
		player->setMap(gameMap);
		player->initPosition(gameMap->getStartPoint());
		Camera::setTarget(player->transform.pos);
	}

	void BossStage::resetMap()
	{
		EnemyManager::getIns()->claerList();
		BulletManager::getIns()->claerList();
		ItemManager::getIns()->claerList();
		EventManager::getIns()->claerList();
	}
}