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

	namespace Static {
		using MapStageList = std::vector<std::vector<std::string>>;

		static MapStageList mapStageList(4);     // �}�b�v�X�e�[�W�̃t�@�C�����X�g
	}

	GameScene::GameScene(SceneManager* _sceneManager)
		: sceneManager(_sceneManager)
		, backGround()
		, gameMap(new Map{ this })
		, player()
		, currentMapNumber(0)
	{
		Static::mapStageList[0].push_back("TestMap_1");
		Static::mapStageList[0].push_back("TestMap_2");
		Static::mapStageList[0].push_back("TestMap_3");
		Static::mapStageList[0].push_back("TestMap_4");

		Static::mapStageList[1].push_back("TestMap_1");
		Static::mapStageList[1].push_back("TestMap_2");
		Static::mapStageList[1].push_back("TestMap_3");
		Static::mapStageList[1].push_back("TestMap_4");

		Static::mapStageList[2].push_back("TestMap_1");
		Static::mapStageList[2].push_back("TestMap_2");
		Static::mapStageList[2].push_back("TestMap_3");
		Static::mapStageList[2].push_back("TestMap_4");

		Static::mapStageList[3].push_back("TestMap_1");
		Static::mapStageList[3].push_back("TestMap_2");
		Static::mapStageList[3].push_back("TestMap_3");
		Static::mapStageList[3].push_back("TestMap_4");
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
		initMap();
	}

	void GameScene::onUpdate()
	{

		if (Input::getKeyDown(Key::S)) {
			//sceneManager->changeScene(SceneType::Title);
			backGround.setTexture(1);
		}

		if (Input::getKeyDown(Key::D)) {
			//sceneManager->changeScene(SceneType::Title);
			backGround.setTexture(0);
		}

		backGround.draw();
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

	void GameScene::initMap()
	{
		// Manager�̃��X�g�����ׂď���
		resetMap();

		// 
		backGround.setTexture(0);

		// ���݂̃}�b�v�ԍ���0�ɂ���
		currentMapNumber = 0;

		// �}�b�v���N���A����
		gameMap->claerMap();

		// �}�b�v��ǂݍ���
		//auto mapFile = global::MapAsset(Static::mapStageList[StageManager::getIns()->getCurrentStage()][currentMapNumber]);
		auto mapFile = "Asset/MapData/Test/TestFeild";
		gameMap->loadMapFile(mapFile);

		// �J�������}�b�v�Ɏ��߂�
		Camera::setMapInfo(gameMap->getMapSize());

		// �v���C���[�̈ʒu�ݒ�
		player.onStart();
		player.setMap(gameMap);
		player.initPosition(gameMap->getStartPoint());
	}

	void GameScene::nextMap()
	{
		// Manager�̃��X�g�����ׂď���
		resetMap();

		// �}�b�v�̐���1�i�߂�
		currentMapNumber = (currentMapNumber + 1) % 4;

		// �}�b�v���N���A����
		gameMap->claerMap();

		// �}�b�v��ǂݍ���
		auto mapFile = global::MapAsset(Static::mapStageList[StageManager::getIns()->getCurrentStage()][currentMapNumber]);
		gameMap->loadMapFile(mapFile);

		// �J�������}�b�v�Ɏ��߂�
		Camera::setMapInfo(gameMap->getMapSize());

		// �v���C���[�̈ʒu�ݒ�
		player.setMap(gameMap);
		player.initPosition(gameMap->getStartPoint());
	}

	void GameScene::changeSelectScene()
	{
		sceneManager->changeScene(SceneType::Select);
	}

}
