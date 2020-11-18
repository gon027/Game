#include "../include/BulletManager.h"
#include "../include/Bullet.h"

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
			if (bullet) {
				bullet->onUpdate();
			}
		}
	}

	void BulletManager::collisionActor(EnemyPtr& _enemy)
	{
		for (auto& bullet : bulletList) {
			if (!bullet) {
				continue;
			}

			// ƒvƒŒƒCƒ„[‚ª•ú‚Á‚½’e‚Æ“G‚ªÚG‚µ‚½ê‡
			if (bullet->getBulletType() == BulletType::Player) {
				if (bullet->hit(_enemy)) {
					_enemy->setActive(false);
				}
			}
		}
	}

	void BulletManager::claerList()
	{
		bulletList.clear();
	}

}
