#include "BulletManager.h"
#include "include/Bullet.h"

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
		Debug::drawFormatText(0, 200, Color::Red, "%d", bulletList.size());
		for (auto& bullet : bulletList) {
			if (bullet) {
				bullet->onUpdate();
			}
		}
	}

	void BulletManager::claerList()
	{
		bulletList.clear();
	}

}
