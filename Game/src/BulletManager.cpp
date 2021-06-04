#include "../include/BulletManager.h"
#include "../include/EnemyManager.h"
#include "../include/Player.h"
#include "../include/Bullet.h"
#include "../include/Map.h"
#include "../include/MapBlock.h"
#include "CollisionManager.h"
#include <algorithm>
#include <functional>

namespace gnGame {

	void BulletManager::createBullet(const Vector2& _position, const Vector2& _velocity, float _attack)
	{
		BulletPtr bullet{ new Bullet{_position, _velocity} };
		bullet->onStart();
		bullet->setAttack(_attack);
		bulletList.emplace_back(bullet);
		CollisionManager::getIns()->addBullet(bullet);
	}

	void BulletManager::onUpdate()
	{
		std::for_each(bulletList.begin(), bulletList.end(), [](BulletPtr& _bullet) {
			if (!_bullet->getActive()) {
				return;
			}

			_bullet->onUpdate();
		});
	}

	void BulletManager::onDraw()
	{
		std::for_each(bulletList.begin(), bulletList.end(), [](BulletPtr& _bullet) {
			if (!_bullet->getActive()) {
				return;
			}

			_bullet->onDraw();
		});
	}
	
	void BulletManager::clearList()
	{
		bulletList.clear();
	}
}