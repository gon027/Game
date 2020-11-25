#include "../include/Enemy.h"
#include "../include/Camera.h"
#include "../include/Bullet.h"
#include "../include/TextureManager.h"
#include "../include/BulletManager.h"

namespace gnGame {

	namespace EnemyParameters {

		// �d��
		constexpr float Gravity = 0.980f;

		// �ő�̏d��
		constexpr float MaxGravity = Gravity * 10.0f;

		// �v���C���[���i�ޑ���
		constexpr float Speed = 350.0f;

		// �v���C���[�̃W�����v��
		constexpr float JumpPower = -7.0f;
	}

	// ���������߂�
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

    Enemy::Enemy()
		: IActor()
		, dir(Direction::Right)
        , sprite()
    {
		this->name = "Enemy";
    }

	Enemy::Enemy(const Vector2& _pos)
		: IActor()
		, dir(Direction::Right)
		, sprite()
	{
		this->name = "Enemy";
		this->transform.setPos(_pos);
	}

    void Enemy::onStart()
    {
		sprite.setTexture(TextureManager::getTexture("Enemy"));

        bounds.minPos.setPos(0, 0);
        bounds.maxPos.setPos(32, 32);
        bounds.size.setPos(bounds.maxPos - bounds.minPos);
        bounds.center.setPos(bounds.size.half());
    }

    void Enemy::onUpdate()
    {

		// �����Ă��邩
		if (!this->isActive) {
			return;
		}

		moveEnemy();
		shotEnemy();

		this->transform.pos = intersectTileMap();

		// ��ʊO�����肷��
		// ��ʊO�������ꍇ�`�悵�Ȃ�
		if (!this->isOnScreen()) {
			return;
		}

		auto screen{ Camera::toScreenPos(this->transform.pos) };
		collider.update(screen, 32.0f, 32.0f);
		sprite.draw(screen, transform.scale, transform.angle, true, isFlip);
    }

    Vector2 Enemy::intersectTileMap()
    {
		auto nextPos = this->transform.pos + velocity;

		// ������s�����W�����߂�
		float offX{ bounds.center.x / 4.0f - 1.0f };
		float offY{ bounds.center.y / 4.0f - 1.0f };

		// �㉺����p�̂ɔ���{�b�N�X�X�V
		bounds.minPos.setPos(this->transform.pos.x - bounds.center.x, nextPos.y - bounds.center.y);
		bounds.maxPos.setPos(this->transform.pos.x + bounds.center.x, nextPos.y + bounds.center.y);

		// -- �� --
		intersectPoint.bottom[0] = Vector2{ bounds.minPos.x + offX, bounds.maxPos.y + 1.0f };
		intersectPoint.bottom[1] = Vector2{ bounds.maxPos.x - offX, bounds.maxPos.y + 1.0f };

		// -- �� --
		intersectPoint.top[0] = Vector2{ bounds.minPos.x + offX, bounds.minPos.y - 1.0f };
		intersectPoint.top[1] = Vector2{ bounds.maxPos.x - offX, bounds.minPos.y - 1.0f };

		// -- ��Ƃ̓����蔻�� --
		for (int i{}; i < IntersectPoint::Size; ++i) {

			if (map->checkTile((int)intersectPoint.top[i].x, (int)intersectPoint.top[i].y)) {
				auto hitPos = ((int)intersectPoint.top[i].y / MapInfo::MapSize + 1) * (float)MapInfo::MapSize;

				if (intersectPoint.top[i].y <= hitPos) {
					nextPos.y = nextPos.y + fabsf(intersectPoint.top[i].y - hitPos) - 1.0f;

					break;
				}
			}
		}

		// -- ���Ƃ̓����蔻�� --
		for (int i{}; i < IntersectPoint::Size; ++i) {

			if (map->checkTile((int)intersectPoint.bottom[i].x, (int)intersectPoint.bottom[i].y)) {
				auto hitPos = (int)(intersectPoint.bottom[i].y / MapInfo::MapSize) * (float)MapInfo::MapSize;

				if (intersectPoint.bottom[i].y >= hitPos) {
					nextPos.y = nextPos.y - fabsf(intersectPoint.bottom[i].y - hitPos) + 1.0f;
					break;
				}
			}
		}

		// ���E����p�ɔ���{�b�N�X�X�V
		bounds.minPos.setPos(nextPos.x - bounds.center.x, this->transform.pos.y - bounds.center.y);
		bounds.maxPos.setPos(nextPos.x + bounds.center.x, this->transform.pos.y + bounds.center.y);

		// -- �E --
		intersectPoint.right[0] = Vector2{ bounds.maxPos.x , bounds.minPos.y + offY };
		intersectPoint.right[1] = Vector2{ bounds.maxPos.x , bounds.maxPos.y - offY };

		// -- �� --
		intersectPoint.left[0] = Vector2{ bounds.minPos.x - 1.0f, bounds.minPos.y + offY };
		intersectPoint.left[1] = Vector2{ bounds.minPos.x - 1.0f, bounds.maxPos.y - offY };


		// -- �E�Ƃ̓����蔻�� --
		for (int i{}; i < IntersectPoint::Size; ++i) {

			if (map->checkTile((int)intersectPoint.right[i].x, (int)intersectPoint.right[i].y)) {
				float hitPos = (int)(intersectPoint.right[i].x / MapInfo::MapSize) * (float)MapInfo::MapSize;

				if (intersectPoint.right[i].x >= hitPos) {
					nextPos.x = nextPos.x - fabsf(intersectPoint.right[i].x - hitPos);
					dir = Direction::Left;
					isFlip = false;
					break;
				}
			}
		}

		// -- ���Ƃ̓����蔻�� --		
		for (int i{}; i < IntersectPoint::Size; ++i) {

			if (map->checkTile((int)intersectPoint.left[i].x, (int)intersectPoint.left[i].y)) {
				float hitPos = ((int)intersectPoint.left[i].x / MapInfo::MapSize + 1) * (float)MapInfo::MapSize;

				if (intersectPoint.left[i].x <= hitPos) {
					nextPos.x = nextPos.x + fabsf(intersectPoint.left[i].x - hitPos) - 1.0f;
					dir = Direction::Right;
					isFlip = true;
					break;
				}
			}
		}

		return nextPos;
    }

    void Enemy::setMap(Map* _map)
    {
        map = _map;
    }

	BoxCollider& Enemy::getCollider()
	{
		return collider;
	}

	void Enemy::moveEnemy()
	{
		velocity.setPos(getDirection(dir));
		velocity.x *= 2.0f;
		velocity.y = 1.0f;
	}

	void Enemy::shotEnemy()
	{
		bframe++;

		if (bframe >= 30) {
			if (dir == Direction::Left) {
				BulletPtr bulletPtr(new Bullet(this->transform.pos, Vector2{ -10.0f, 0.0f }));
				bulletPtr->onStart();
				BulletManager::getIns()->addBullet(bulletPtr);
			}
			else if (dir == Direction::Right) {
				BulletPtr bulletPtr(new Bullet(this->transform.pos, Vector2{ 10.0f, 0.0f }));
				bulletPtr->onStart();
				BulletManager::getIns()->addBullet(bulletPtr);
			}
			bframe = 0;
		}
	}
}