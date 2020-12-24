#include "../include/BulletManager.h"
#include "../include/EnemyManager.h"
#include "../include/Player.h"
#include "../include/Bullet.h"
#include "../include/Enemy.h"
#include "../include/Map.h"

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
		//Debug::drawFormatText(0, 200, Color::Red, "BulletList = %d", bulletList.size());

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

	void BulletManager::collisionActor(Player& _player)
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
				// �v���C���[���ł����e�̎�
				if (bulletType == BulletType::Player) {
					if (bullet->hit(EnemyManager::getIns()->getEnemy(i))) {
						//EnemyManager::getIns()->removeActor(i);
						EnemyManager::getIns()->getEnemy(i)->getEnemyBody().damage(bullet->getAttack());

						if (EnemyManager::getIns()->getEnemy(i)->getParameter().hp <= 0) {
							EnemyManager::getIns()->removeActor(i);
						}

						bullet = nullptr;
						return;
					}
				}
				// �G���ł����e�̎�
				else if (bulletType == BulletType::Enemy) {
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
