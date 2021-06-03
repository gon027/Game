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

	void DebugStage::nextMap()
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

	void DebugStage::resetMap()
	{
	}

}