#include "../include/BulletManager.h"
#include "../include/EnemyManager.h"
#include "../include/Player.h"
#include "../include/Bullet.h"
#include "../include/Enemy.h"
#include "../include/Map.h"
#include "../include/GameScene.h"
#include "../include/Map.h"
#include "../include/MapBlock.h"

namespace gnGame {

	BulletManager* BulletManager::getIns()
	{
		static BulletManager Instance;
		return &Instance;
	}

	BulletManager::~BulletManager()
	{
	}

	void BulletManager::addBullet(BulletPtr& _bullet)
	{
		for (size_t i{ 0 }; i < bulletList.size(); ++i) {
			if (!bulletList[i]) {
				bulletList[i] = _bullet;
				return;
			}
		}

		bulletList.emplace_back(_bullet);
	}

	void BulletManager::removeBullet(BulletPtr& _bullet)
	{
	}

	void BulletManager::onUpdateBulletList()
	{
		for (auto& bullet : bulletList) {
			if (!bullet) {
				continue;
			}

			bullet->onUpdate();

			// �����Œe����ʊO�ɏo����폜
			if (!bullet->isOnScreen()) {
				bullet = nullptr;
			}
		}
	}

	// TODO: �֐����̂��傫���Ȃ��Ă��Ă���̂ŁA������������
	void BulletManager::collisionActor(Player& _player, GameScene* _gameScene)
	{
		// �G�̃��X�g��S�T��
		for (size_t i{ 0 }; i < EnemyManager::getIns()->getListSize(); ++i) {
			if (!EnemyManager::getIns()->getEnemy(i)) {
				continue;
			}

			// �e�̃��X�g��S�T��
			for (auto& bullet : bulletList) {
				if (!bullet) {
					continue;
				}

				auto bulletType = bullet->getBulletType();

				// ����ǂɂ��������Ƃ��̏���
				auto gameMap = _gameScene->getMap();
				for (int i{ 0 }; i < gameMap->getMapObjectList().size(); ++i) {
					// �e�ƃ}�b�v��̃I�u�W�F�N�g�̓����蔻��
					if (bullet->getCollider().isHitTest(gameMap->getMapBlock(i).getCollider())) {
						//gameMap->removeMapMapObject(i);
						bullet = nullptr;
						return;
					}
				}

				// �v���C���[���ł����e�̎�
				if (bulletType == BulletType::Player) {
					if (bullet->hit(EnemyManager::getIns()->getEnemy(i))) {
						auto enemy = EnemyManager::getIns()->getEnemy(i);	
						enemy->getEnemyBody().damage(bullet->getAttack());

						if (enemy->getEnemyType() == EnemyType::Nomal) {
							// ���ʂ̓G�̏ꍇ
							if (EnemyManager::getIns()->getEnemy(i)->getParameter().hp <= 0) {
								EnemyManager::getIns()->removeActor(i);
							}
						}
						else if (enemy->getEnemyType() == EnemyType::Boss) {
							// �{�X��|�����Ƃ��̏ꍇ
							if (EnemyManager::getIns()->getEnemy(i)->getParameter().hp <= 0) {
								_gameScene->changeSelectScene();
							}
						}

						bullet = nullptr;
						return;
					}
				}
				else if (bulletType == BulletType::Enemy) {
					// �G���ł����e�̎�
					if (bullet->hit(_player)) {
						_player.getPlayerBody().damage(bullet->getAttack());

						if (_player.getPlayerBody().getParameter().hp <= 0) {
							_player.setActive(false);
						}

						bullet = nullptr;
						return;
					}
				}
			}
		}
	}

	void BulletManager::collisionMap(Map& _map)
	{
		for (auto& bullet : bulletList) {
			if (!bullet) {
				continue;
			}

			// �v���C���[���������e�ƓG���ڐG�����ꍇ
			if (bullet->intersectMap(_map)) {
				bullet = nullptr;
			}
		}
		
	}

	void BulletManager::claerList()
	{
		// �z���nullptr�Ŗ��߂�
		for (size_t i{ 0 }; i < bulletList.size(); ++i) {
			if (bulletList[i]) {
				bulletList[i] = nullptr;
			}
		}
	}
}