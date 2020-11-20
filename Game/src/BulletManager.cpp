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

			// ここで弾が画面外に出たら削除
			if (!bullet->onScreen()) {
				bullet = nullptr;
			}
		}
	}

	void BulletManager::collisionActor(Player& _player)
	{
		// 敵と弾のリストを全探索
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

			// プレイヤーが放った弾と敵が接触した場合
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
