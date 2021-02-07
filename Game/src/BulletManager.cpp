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

			// ここで弾が画面外に出たら削除
			if (!bullet->isOnScreen()) {
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

				/*
				// 壊れる壁にあたったときの処理
				auto gameMap = _gameScene->getMap();
				for (int i{ 0 }; i < gameMap->getMapObjectList().size(); ++i) {
					// 弾とマップ上のオブジェクトの当たり判定
					if (bullet->getCollider().isHitTest(gameMap->getMapBlock(i).getCollider())) {
						//gameMap->removeMapMapObject(i);
						bullet = nullptr;
						return;
					}
				}
				*/

				// プレイヤーが打った弾の時
				if (bulletType == BulletType::Player) {
					if (bullet->hit(EnemyManager::getIns()->getEnemy(i))) {
						auto enemy = EnemyManager::getIns()->getEnemy(i);	
						enemy->getEnemyBody().damage(bullet->getAttack());

						// エフェクトを出すかどうかのフラグ
						bool isEffect = false;
						auto v = enemy->transform.pos;
						if (enemy->getEnemyType() == EnemyType::Nomal) {
							// 普通の敵の場合
							if (EnemyManager::getIns()->getEnemy(i)->getParameter().hp <= 0) {
								EnemyManager::getIns()->removeActor(i);
								isEffect = true;
							}
						}
						else if (enemy->getEnemyType() == EnemyType::Boss) {
							// ボスを倒したときの場合
							if (EnemyManager::getIns()->getEnemy(i)->getParameter().hp <= 0) {
								_gameScene->changeSelectScene();
							}
						}

						// 死亡した際のエフェクトを出す
						if (isEffect) {
							auto vv = Camera::toScreenPos(v);
							EffectManager::getIns()->draw(0, vv, { 3, 3 });
						}

						bullet = nullptr;
						return;
					}
				}
				else if (bulletType == BulletType::Enemy) {
					// 敵が打った弾の時
					if (bullet->hit(_player)) {
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
		// 配列をnullptrで埋める
		for (size_t i{ 0 }; i < bulletList.size(); ++i) {
			if (bulletList[i]) {
				bulletList[i] = nullptr;
			}
		}
	}
}