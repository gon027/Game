#include "../include/Enemy.h"
#include "../include/Camera.h"
#include "../include/Bullet.h"
#include "../include/TextureManager.h"
#include "../include/BulletManager.h"

namespace gnGame {

	namespace EnemyParameters {

		// 重力
		constexpr float Gravity = 0.980f;

		// 最大の重力
		constexpr float MaxGravity = Gravity * 10.0f;

		// プレイヤーが進む速さ
		constexpr float Speed = 350.0f;

		// プレイヤーのジャンプ力
		constexpr float JumpPower = -7.0f;
	}

	// 方向を決める
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
		, enemyBody({})
		, enemyType(EnemyType::Nomal)
		, actionState(EnemyActionState::Wait)
		, isGround(false)
    {
		this->name = "Enemy";
    }

	Enemy::Enemy(const Vector2& _pos, const ActorParameter _parameter, const EnemyType _enemyType)
		: IActor()
		, dir(Direction::Right)
		, sprite()
		, enemyBody(_parameter)
		, enemyType(_enemyType)
		, actionState(EnemyActionState::Wait)
		, isGround(false)
	{
		this->name = "Enemy";
		this->transform.setPos(_pos);
	}

    void Enemy::onStart()
    {

    }

    void Enemy::onUpdate()
    {

    }

    Vector2 Enemy::intersectTileMap()
    {
		auto nextPos = this->transform.pos + velocity;

		// 判定を行う座標を決める
		float offX{ bounds.center.x / 4.0f - 1.0f };
		float offY{ bounds.center.y / 4.0f - 1.0f };

		// 上下判定用のに判定ボックス更新
		bounds.minPos.setPos(this->transform.pos.x - bounds.center.x, nextPos.y - bounds.center.y);
		bounds.maxPos.setPos(this->transform.pos.x + bounds.center.x, nextPos.y + bounds.center.y);

		// -- 下 --
		intersectPoint.bottom[0] = Vector2{ bounds.minPos.x + offX, bounds.maxPos.y + 1.0f };
		intersectPoint.bottom[1] = Vector2{ bounds.maxPos.x - offX, bounds.maxPos.y + 1.0f };

		// -- 上 --
		intersectPoint.top[0] = Vector2{ bounds.minPos.x + offX, bounds.minPos.y - 1.0f };
		intersectPoint.top[1] = Vector2{ bounds.maxPos.x - offX, bounds.minPos.y - 1.0f };

		nextPos = checkUpperBlock(intersectPoint.top, nextPos);
		nextPos = checkLowerBlock(intersectPoint.bottom, nextPos);

		// 左右判定用に判定ボックス更新
		bounds.minPos.setPos(nextPos.x - bounds.center.x, this->transform.pos.y - bounds.center.y);
		bounds.maxPos.setPos(nextPos.x + bounds.center.x, this->transform.pos.y + bounds.center.y);

		// -- 右 --
		intersectPoint.right[0] = Vector2{ bounds.maxPos.x , bounds.minPos.y + offY };
		intersectPoint.right[1] = Vector2{ bounds.maxPos.x , bounds.maxPos.y - offY };

		// -- 左 --
		intersectPoint.left[0] = Vector2{ bounds.minPos.x - 1.0f, bounds.minPos.y + offY };
		intersectPoint.left[1] = Vector2{ bounds.minPos.x - 1.0f, bounds.maxPos.y - offY };

		nextPos = checkRightBlock(intersectPoint.right, nextPos);
		nextPos = checkLeftBlock(intersectPoint.left, nextPos);

		return nextPos;
    }

    void Enemy::setMap(Map* _map)
    {
        map = _map;
    }

	Direction Enemy::getDir()
	{
		return dir;
	}

	BoxCollider& Enemy::getCollider()
	{
		return collider;
	}

	EnemyBody& Enemy::getEnemyBody()
	{
		return enemyBody;
	}

	ActorParameter& Enemy::getParameter()
	{
		return enemyBody.getParameter();
	}

	const EnemyType Enemy::getEnemyType()
	{
		return enemyType;
	}

	void Enemy::moveEnemy()
	{
		velocity.setPos(getDirection(dir));
		velocity.x *= 2.0f;
	}

	void Enemy::physics()
	{
		if (!isGround) {
			velocity.y += EnemyParameters::Gravity;
			velocity.y = min(velocity.y, EnemyParameters::MaxGravity);
		}
		else {
			velocity.y = 0.0f;
		}
	}

	Vector2 Enemy::checkUpperBlock(const std::vector<Vector2>& _checkPoints, const Vector2& _nextPos)
	{
		auto result = _nextPos;

		for (size_t i{ 0 }; i < _checkPoints.size(); ++i) {
			if (map->checkTile((int)_checkPoints[i].x, (int)_checkPoints[i].y)) {
				auto hitPos = ((int)_checkPoints[i].y / MapInfo::MapSize + 1) * (float)MapInfo::MapSize;

				if (_checkPoints[i].y <= hitPos) {
					result.y = result.y + fabsf(_checkPoints[i].y - hitPos) - 1.0f;

					break;
				}
			}
		}

		return result;
	}

	Vector2 Enemy::checkLowerBlock(const std::vector<Vector2>& _checkPoints, const Vector2& _nextPos)
	{
		auto result = _nextPos;

		for (size_t i{ 0 }; i < _checkPoints.size(); ++i) {
			if (map->checkTile((int)_checkPoints[i].x, (int)_checkPoints[i].y)) {
				auto hitPos = (int)(_checkPoints[i].y / MapInfo::MapSize) * (float)MapInfo::MapSize;

				if (_checkPoints[i].y >= hitPos) {
					result.y = result.y - fabsf(_checkPoints[i].y - hitPos) + 1.0f;
					isGround = true;
					break;
				}
			}
			else {
				isGround = false;
			}
		}

		return result;
	}

	Vector2 Enemy::checkRightBlock(const std::vector<Vector2>& _checkPoints, const Vector2& _nextPos)
	{
		auto result = _nextPos;

		for (size_t i{ 0 }; i < _checkPoints.size(); ++i) {
			if (map->checkTile((int)_checkPoints[i].x, (int)_checkPoints[i].y)) {
				float hitPos = (int)(_checkPoints[i].x / MapInfo::MapSize) * (float)MapInfo::MapSize;

				if (intersectPoint.right[i].x >= hitPos) {
					result.x = result.x - fabsf(_checkPoints[i].x - hitPos);
					dir = Direction::Left;
					isFlip = false;
					break;
				}
			}
		}

		return result;
	}

	Vector2 Enemy::checkLeftBlock(const std::vector<Vector2>& _checkPoints, const Vector2& _nextPos)
	{
		auto result = _nextPos;

		for (size_t i{ 0 }; i < _checkPoints.size(); ++i) {
			if (map->checkTile((int)_checkPoints[i].x, (int)_checkPoints[i].y)) {
				float hitPos = ((int)_checkPoints[i].x / MapInfo::MapSize + 1) * (float)MapInfo::MapSize;


				if (_checkPoints[i].x <= hitPos) {
					result.x = result.x + fabsf(_checkPoints[i].x - hitPos) - 1.0f;
					dir = Direction::Right;
					isFlip = true;
					break;
				}

			}
		}

		return result;
	}
}