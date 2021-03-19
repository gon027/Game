#include "../include/BulletManager.h"
#include "../include/EnemyManager.h"
#include "../include/Player.h"
#include "../include/Bullet.h"
#include "../include/Enemy.h"
#include "../include/Map.h"
#include "../include/GameScene.h"
#include "../include/Map.h"
#include "../include/MapBlock.h"
#include "../EffectManager.h"
#include "../include/Camera.h"

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

	void BulletManager::onUpdateBulletList()
	{
		for (auto& bullet : bulletList) {
			if (!bullet) {
				continue;
			}

			bullet->onUpdate();

			// ‚±‚±‚Å’e‚ª‰æ–ÊŠO‚Éo‚½‚çíœ
			if (!Camera::isOnScreen(bullet->transform.pos)) {
				bullet = nullptr;
			}
		}
	}

	// TODO: ŠÖ”©‘Ì‚ª‘å‚«‚­‚È‚Á‚Ä‚«‚Ä‚¢‚é‚Ì‚ÅA¬‚³‚­‚³‚¹‚é
	void BulletManager::collisionActor(Player& _player, GameScene* _gameScene)
	{
		// “G‚ÌƒŠƒXƒg‚ğ‘S’Tõ
		for (size_t i{ 0 }; i < EnemyManager::getIns()->getListSize(); ++i) {
			if (!EnemyManager::getIns()->getEnemy(i)) {
				continue;
			}

			// ’e‚ÌƒŠƒXƒg‚ğ‘S’Tõ
			for (auto& bullet : bulletList) {
				if (!bullet) {
					continue;
				}

				auto bulletType = bullet->getBulletType();

				// ƒvƒŒƒCƒ„[‚ª‘Å‚Á‚½’e‚Ì
				if (bulletType == BulletType::Player) {
					if (bullet->hitEnemy(EnemyManager::getIns()->getEnemy(i))) {
						auto enemy = EnemyManager::getIns()->getEnemy(i);	
						enemy->getEnemyBody().damage(bullet->getAttack());

						auto v = enemy->transform.pos;
						if (enemy->getEnemyType() == EnemyType::Nomal) {
							// •’Ê‚Ì“G‚Ìê‡
							if (EnemyManager::getIns()->getEnemy(i)->getParameter().hp <= 0) {
								EnemyManager::getIns()->removeActor(i);
							}
						}
						else if (enemy->getEnemyType() == EnemyType::Boss) {
							// ƒ{ƒX‚ğ“|‚µ‚½‚Æ‚«‚Ìê‡
							if (EnemyManager::getIns()->getEnemy(i)->getParameter().hp <= 0) {
								_gameScene->nextMap();
							}
						}

						bullet = nullptr;
						return;
					}
				}
				else if (bulletType == BulletType::Enemy) {
					// “G‚ª‘Å‚Á‚½’e‚Ì
					if (bullet->hitPlayer(_player)) {
						_player.getPlayerBody().damage(bullet->getAttack());

						if (_player.getPlayerBody().getParameter().hp <= 0) {
							_player.death();
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

			// ƒvƒŒƒCƒ„[‚ª•ú‚Á‚½’e‚Æ“G‚ªÚG‚µ‚½ê‡
			if (bullet->intersectMap(_map)) {
				bullet = nullptr;
			}
		}
		
	}

	void BulletManager::claerList()
	{
		bulletList.clear();
	}
}