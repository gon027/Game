#include "CollisionManager.h"
#include "../include/GameObject.h"
#include "../include/Player.h"
#include "../include/Bullet.h"
#include <algorithm>

namespace gnGame {

	void CollisionManager::setPlayer(PlayerPtr& _player)
	{
		player = _player;
	}

	void CollisionManager::addBullet(const BulletPtr& _bullet)
	{
		bulletColliderList.emplace_back(_bullet);
	}
	
	void CollisionManager::addActor(const ActorPtr& _actor)
	{
		actorColliderList.emplace_back(_actor);
	}
	
	void CollisionManager::addObject(const GameObjectPtr& _object)
	{
		objectColliderList.emplace_back(_object);
	}
	
	void CollisionManager::onUpdate()
	{
		// �v���C���[ vs �G
		{
			for (auto& enemy : actorColliderList) {
				if (Collision2D::isCollision(enemy->getCollider(), player->getCollider())) {
					player->onCollision(enemy);
				}
			}
		}

		// �v���C���[ vs �e
		{
			for (auto& bullet : bulletColliderList) {
				if (Collision2D::isCollision(bullet->getCollider(), player->getCollider())) {
					bullet->onCollision(player);
				}
			}
		}

		// �v���C���[ vs �I�u�W�F�N�g
		{
			for (auto& object : objectColliderList) {

			}
		}

		// �G vs �e
		{
			for (auto& bullet : bulletColliderList) {
				for (auto& enemy : actorColliderList) {
					if (Collision2D::isCollision(bullet->getCollider(), enemy->getCollider())) {
						bullet->onCollision(enemy);
					}
				}
			}
		}
	}

	void CollisionManager::clearList()
	{
		bulletColliderList.clear();
		actorColliderList.clear();
		objectColliderList.clear();
	}

}