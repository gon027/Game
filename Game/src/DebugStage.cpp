#include "../include/Stage.h"
#include "../include/TextureManager.h"
#include "../include/UIDrawer.h"
#include "../include/Camera.h"
#include "../include/Map.h"
#include "../include/Player.h"
#include "../include/ObjectManager.h"
#include "../include/Global.h"

namespace gnGame {

	DebugStage::DebugStage(Map* _map, Player* _player)
		: mapNameList()
		, backGround()
		, gameMap(_map)
		, player(_player)
		, currentMapNumber() 
	{
		backGround.setTexture(0);

		mapNameList.push_back("BossStage/Stage_1");
	}

	void DebugStage::onStart()
	{
		initMap();

		ObjectManager::getIns()->onStart();
	}

	void DebugStage::onUpdate()
	{
		ObjectManager::getIns()->onUpdate();

		gameMap->drawMap();
		ObjectManager::getIns()->onDraw();
	}

	void DebugStage::onFinal()
	{
	}

	void DebugStage::initMap()
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

	void DebugStage::nextMap()
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

	void DebugStage::resetMap()
	{
	}

}