#include "../include/BulletManager.h"
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

			// Todo : Bullet����ʊO�ɏo�������肷��
		}
	}

	void BulletManager::collisionActor(EnemyPtr& _enemy)
	{
		for (auto& bullet : bulletList) {
			if (!bullet) {
				continue;
			}

			// �v���C���[���������e�ƓG���ڐG�����ꍇ
			if (bullet->getBulletType() == BulletType::Player) {
				if (bullet->hit(_enemy)) {
					_enemy->setActive(false);
					//bullet->setActive(false);
					bullet = nullptr;
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
		bulletList.clear();
	}

}
