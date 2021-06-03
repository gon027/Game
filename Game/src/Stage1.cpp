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

	Stage1::Stage1(Map* _map, Player* _player)
		: mapNameList()
		, backGround()
		, gameMap(_map)
		, player(_player)
		, currentMapNumber()
	{
		backGround.setTexture(0);

		mapNameList.push_back("Stage1/Map_1");
		mapNameList.push_back("Stage1/Map_2");
		mapNameList.push_back("Stage1/Map_3");
		mapNameList.push_back("Stage1/Map_4");
	}

	void Stage1::onStart()
	{
		initMap();

		AudioManager::getIns()->play("BGM_game", PlayType::Loop);
	}

	void Stage1::onUpdate()
	{
		// �w�i�̕`��
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

	void Stage1::onFinal()
	{
		AudioManager::getIns()->stop("BGM_game");
		AudioManager::getIns()->setPosition("BGM_game", 0);

		resetMap();
	}

	void Stage1::initMap()
	{
		// ���݂̃}�b�v�ԍ���0�ɂ���
		currentMapNumber = 0;

		// �}�b�v���N���A����
		gameMap->claerMap();

		// �}�b�v��ǂݍ���
		auto mapFile = global::MapAsset(mapNameList[currentMapNumber]);
		gameMap->loadMapFile(mapFile);

		// �J�������}�b�v�Ɏ��߂�
		Camera::setMapInfo(gameMap->getMapSize());

		// �v���C���[�̈ʒu�ݒ�
		player->onStart();
		player->setMap(gameMap);
		player->initPosition(gameMap->getStartPoint());
		Camera::setTarget(player->transform.pos);
	}

	void Stage1::nextMap()
	{
		player->setIsMove(false);

		// Manager�̃��X�g�����ׂď���
		resetMap();

		// �}�b�v�̐���1�i�߂�
		currentMapNumber = (currentMapNumber + 1) % 4;

		// �}�b�v���N���A����
		gameMap->claerMap();

		// �}�b�v��ǂݍ���
		auto mapFile = global::MapAsset(mapNameList[currentMapNumber]);
		gameMap->loadMapFile(mapFile);

		// �J�������}�b�v�Ɏ��߂�
		Camera::setMapInfo(gameMap->getMapSize());

		// �v���C���[�̈ʒu�ݒ�
		player->setMap(gameMap);
		player->initPosition(gameMap->getStartPoint());
		Camera::setTarget(player->transform.pos);
	}

	void Stage1::resetMap()
	{
		EnemyManager::getIns()->claerList();
		BulletManager::getIns()->claerList();
		ItemManager::getIns()->claerList();
		EventManager::getIns()->claerList();
	}
}