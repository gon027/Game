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

			// ‚±‚±‚Å’e‚ª‰æ–ÊŠO‚Éo‚½‚çíœ
			if (!bullet->isOnScreen()) {
				bullet = nullptr;
			}
		}
	}

	void BulletManager::collisionActor(Player& _player)
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
				// “G‚ª‘Å‚Á‚½’e‚Ì
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

			// ƒvƒŒƒCƒ„[‚ª•ú‚Á‚½’e‚Æ“G‚ªÚG‚µ‚½ê‡
			if (bullet->intersectMap(_map)) {
				bullet = nullptr;
			}
		}
		
	}

	void BulletManager::claerList()
	{
		// ”z—ñ‚ğnullptr‚Å–„‚ß‚é
		for (size_t i{ 0 }; i < bulletList.size(); ++i) {
			if (bulletList[i]) {
				bulletList[i] = nullptr;
			}
		}
	}

}
