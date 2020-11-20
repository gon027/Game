#include "../include/BulletManager.h"
#include "../include/EnemyManager.h"
#include "../include/Player.h"
#include "../include/Bullet.h"
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
		Debug::drawFormatText(0, 200, Color::Red, "BulletList = %d", bulletList.size());

		for (auto& bullet : bulletList) {
			if (!bullet) {
				continue;
			}

			bullet->onUpdate();

			// ‚±‚±‚Å’e‚ª‰æ–ÊŠO‚Éo‚½‚çíœ
			if (!bullet->onScreen()) {
				bullet = nullptr;
			}
		}
	}

	void BulletManager::collisionActor(Player& _player)
	{
		// “G‚Æ’e‚ÌƒŠƒXƒg‚ğ‘S’Tõ
		for (size_t i{ 0 }; i < EnemyManager::getIns()->getEnemyList().size(); ++i) {
			if (!EnemyManager::getIns()->getEnemy(i)) {
				continue;
			}

			for (auto& bullet : bulletList) {
				if (!bullet) {
					continue;
				}

				auto bulletType = bullet->getBulletType();

				if (bulletType == BulletType::Player) {
					if (bullet->hit(EnemyManager::getIns()->getEnemy(i))) {
						bullet = nullptr;
						EnemyManager::getIns()->removeActor(i);
						return;
					}
				}
				else if (bulletType == BulletType::Enemy) {
					if (bullet->hit(_player)) {
						bullet = nullptr;
						_player.setActive(false);
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
