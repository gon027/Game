#include "EnemyState.h"
#include "../include/Camera.h"
#include "../include/Bullet.h"
#include "../include/TextureManager.h"
#include "../include/BulletManager.h"


namespace gnGame {
	namespace EnemyState {

		namespace Move {

			EnemyMove::EnemyMove(Enemy* _enemyPtr, Player* _player)
				: enemyPtr(_enemyPtr)
				, playerPtr(_player)
			{
			}

			void EnemyMove::execute()
			{

			}

		}
	}

	namespace EnemyState {

		namespace Attack {

			namespace {
				constexpr float SHOTINTERVAL = 1.0f;
			}

			EnemyAttack::EnemyAttack(Enemy* _enemyPtr)
				: enemyPtr(_enemyPtr)
				, shotTime(0.0f)
			{
			}

			void EnemyAttack::execute()
			{
				shotTime += Time::deltaTime();

				// 1•b‚É1‰ñ‘Å‚Â
				if (shotTime >= SHOTINTERVAL) {
					if (enemyPtr->getDir() == Direction::Left) {
						BulletPtr bulletPtr(new Bullet(enemyPtr->transform.pos, Vector2{ -10.0f, 0.0f }));
						bulletPtr->onStart();
						BulletManager::getIns()->addBullet(bulletPtr);
					}
					else if (enemyPtr->getDir() == Direction::Right) {
						BulletPtr bulletPtr(new Bullet(enemyPtr->transform.pos, Vector2{ 10.0f, 0.0f }));
						bulletPtr->onStart();
						BulletManager::getIns()->addBullet(bulletPtr);
					}
					shotTime = 0;
				}
			}

		}
	}
}

