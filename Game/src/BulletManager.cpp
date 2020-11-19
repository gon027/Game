#include "../include/BulletManager.h"
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

			// Todo : Bullet‚ª‰æ–ÊŠO‚Éo‚½‚©”»’è‚·‚é
		}
	}

	void BulletManager::collisionActor(EnemyPtr& _enemy, Player& _player)
	{
		for (auto& bullet : bulletList) {
			if (!bullet) {
				continue;
			}

			auto bulletType = bullet->getBulletType();

			// ƒvƒŒƒCƒ„[‚ª•ú‚Á‚½’e‚Æ“G‚ªÚG‚µ‚½ê‡
			if (bulletType == BulletType::Player) {
				if (bullet->hit(_enemy)) {
					_enemy->setActive(false);
					//bullet->setActive(false);
					bullet = nullptr;
				}
			}
			else if (bulletType == BulletType::Enemy) {   // “G‚ª•ú‚Á‚½’e‚Ìê‡
				if (bullet->hit(_player)) {
					_player.setActive(false);
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
