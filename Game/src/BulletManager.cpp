#include "../include/BulletManager.h"
#include "../include/EnemyManager.h"
#include "../include/Player.h"
#include "../include/Bullet.h"
#include "../include/Enemy.h"
#include "../include/Map.h"
#include "../include/GameScene.h"
#include "../include/Map.h"
#include "../include/MapBlock.h"
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

			// ここで弾が画面外に出たら削除
			if (!Camera::isOnScreen(bullet->transform.pos)) {
				bullet = nullptr;
			}
		}
	}

	// TODO: 関数自体が大きくなってきているので、小さくさせる
	void BulletManager::collisionActor(Player& _player, GameScene* _gameScene)
	{
		// 敵のリストを全探索
		for (size_t i{ 0 }; i < EnemyManager::getIns()->getListSize(); ++i) {
			if (!EnemyManager::getIns()->getEnemy(i)) {
				continue;
			}

			// 弾のリストを全探索
			for (auto& bullet : bulletList) {
				if (!bullet) {
					continue;
				}

				auto bulletType = bullet->getBulletType();

				// プレイヤーが打った弾の時
				if (bulletType == BulletType::Player) {
					if (bullet->hitEnemy(EnemyManager::getIns()->getEnemy(i))) {
						auto enemy = EnemyManager::getIns()->getEnemy(i);	
						enemy->getEnemyBody().damage(bullet->getAttack());

						if (enemy->getEnemyType() == EnemyType::Nomal) {
							// 普通の敵の場合
							if (EnemyManager::getIns()->getEnemy(i)->getParameter().hp <= 0) {
								EnemyManager::getIns()->removeActor(i);
							}
						}
						else if (enemy->getEnemyType() == EnemyType::Boss) {
							// ボスを倒したときの場合
							if (EnemyManager::getIns()->getEnemy(i)->getParameter().hp <= 0) {
								_gameScene->nextMap();
							}
						}

						bullet = nullptr;
						return;
					}
				}
				else if (bulletType == BulletType::Enemy) {
					// 敵が打った弾の時
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