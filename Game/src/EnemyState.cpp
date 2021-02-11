#include "../include/EnemyState.h"
#include "../include/Camera.h"
#include "../include/Bullet.h"
#include "../include/TextureManager.h"
#include "../include/BulletManager.h"
#include "../include/Player.h"

namespace gnGame {
	namespace EnemyState {

		namespace Move {

			// •ûŒü‚ðŒˆ‚ß‚é
			Vector2 getDirection(Direction _dir) {
				switch (_dir)
				{
				case Direction::Up:    return Vector2::Up;
				case Direction::Down:  return Vector2::Down;
				case Direction::Left:  return Vector2::Left;
				case Direction::Right: return Vector2::Right;
				default:               return Vector2::Zero;
				}
			}

			EnemyMove::EnemyMove(Enemy* _enemyPtr)
				: enemyPtr(_enemyPtr)
				, velocity()
			{
			}

			void EnemyMove::execute()
			{
				velocity.setPos(getDirection(enemyPtr->getDir()));
				velocity.x *= 2.0f;
				velocity.y = 1.0f;
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
					Vector2 shotDir{ (enemyPtr->getDir() == Direction::Left) ? -10.0f : 10.0f, 0.0f };
					BulletPtr bulletPtr(new Bullet(enemyPtr->transform.pos, shotDir));
					bulletPtr->onStart();
					bulletPtr->setAttack(enemyPtr->getParameter().attack);
					BulletManager::getIns()->addBullet(bulletPtr);
					shotTime = 0;
				}
			}

			AimedShotPlayer::AimedShotPlayer(Enemy* _enemyPtr)
				: enemyPtr(_enemyPtr)
				, frameTime()
			{
			}

			void AimedShotPlayer::execute(Player* _player)
			{
				frameTime.update();

				if (frameTime.isTimeUp(1.0f)) {
					const auto playerPos = _player->transform.pos;
					const auto enemyPos = enemyPtr->transform.pos;
					const auto diff = playerPos - enemyPos;
					const float rad = std::atan2(diff.y, diff.x);

					BulletPtr bulletPtr(new Bullet(enemyPtr->transform.pos, { cos(rad) * 5.0f, sin(rad) * 5.0f }));
					bulletPtr->onStart();
					bulletPtr->setAttack(enemyPtr->getParameter().attack);
					BulletManager::getIns()->addBullet(bulletPtr);
					frameTime.reset();
				}
			}
		}
	}
}

