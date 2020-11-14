#include "../include/Enemy.h"
#include "../include/Camera.h"

namespace gnGame {

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
		, dir(Direction::Left)
        , eImage()
    {
    }

    void Enemy::onStart()
    {
		this->name = "Enemy";

        pos.setPos(300, 300);

        bounds.minPos.setPos(0, 0);
        bounds.maxPos.setPos(32, 32);
        bounds.size.setPos(bounds.maxPos - bounds.minPos);
        bounds.center.setPos(bounds.size.half());
    }

    void Enemy::onUpdate(float _deltaTime)
    {
		velocity.setPos(getDirection(dir));
		velocity.x *= _deltaTime;
		velocity.y = 1.f;

		pos = intersectTileMap();
        auto screen{ CameraIns->toScreenPos(pos) };
        eImage.sprite.setPos(screen);
        eImage.sprite.draw();
    }

    Vector2 Enemy::intersectTileMap()
    {
		auto nextPos = pos + velocity;
		Debug::drawFormatText(100, 220, Color::Black, "%s", nextPos.toString().c_str());


		// ������s�����W�����߂�
		float offX{ bounds.center.x / 4.0f - 1.0f };
		float offY{ bounds.center.y / 4.0f - 1.0f };

		// �㉺����p�̂ɔ���{�b�N�X�X�V
		bounds.minPos.setPos(pos.x - bounds.center.x, nextPos.y - bounds.center.y);
		bounds.maxPos.setPos(pos.x + bounds.center.x, nextPos.y + bounds.center.y);

		// -- �� --
		intersectPoint.bottom[0] = Vector2{ bounds.minPos.x + offX, bounds.maxPos.y + 1.0f };
		intersectPoint.bottom[1] = Vector2{ bounds.maxPos.x - offX, bounds.maxPos.y + 1.0f };

		// -- �� --
		intersectPoint.top[0] = Vector2{ bounds.minPos.x + offX, bounds.minPos.y - 1.0f };
		intersectPoint.top[1] = Vector2{ bounds.maxPos.x - offX, bounds.minPos.y - 1.0f };

		// -- ��Ƃ̓����蔻�� --
		for (int i{}; i < IntersectPoint::Size; ++i) {

			if (map.checkTile((int)intersectPoint.top[i].x, (int)intersectPoint.top[i].y)) {
				auto hitPos = ((int)intersectPoint.top[i].y / MapInfo::MapSize + 1) * (float)MapInfo::MapSize;

				if (intersectPoint.top[i].y <= hitPos) {
					nextPos.y = nextPos.y + fabsf(intersectPoint.top[i].y - hitPos) - 1.0f;

					break;
				}
			}
		}

		// -- ���Ƃ̓����蔻�� --
		for (int i{}; i < IntersectPoint::Size; ++i) {

			if (map.checkTile((int)intersectPoint.bottom[i].x, (int)intersectPoint.bottom[i].y)) {
				auto hitPos = (int)(intersectPoint.bottom[i].y / MapInfo::MapSize) * (float)MapInfo::MapSize;

				if (intersectPoint.bottom[i].y >= hitPos) {
					nextPos.y = nextPos.y - fabsf(intersectPoint.bottom[i].y - hitPos) + 1.0f;
					break;
				}
			}
		}

		// ���E����p�ɔ���{�b�N�X�X�V
		bounds.minPos.setPos(nextPos.x - bounds.center.x, pos.y - bounds.center.y);
		bounds.maxPos.setPos(nextPos.x + bounds.center.x, pos.y + bounds.center.y);

		// -- �E --
		intersectPoint.right[0] = Vector2{ bounds.maxPos.x , bounds.minPos.y + offY };
		intersectPoint.right[1] = Vector2{ bounds.maxPos.x , bounds.maxPos.y - offY };

		// -- �� --
		intersectPoint.left[0] = Vector2{ bounds.minPos.x - 1.0f, bounds.minPos.y + offY };
		intersectPoint.left[1] = Vector2{ bounds.minPos.x - 1.0f, bounds.maxPos.y - offY };


		// -- �E�Ƃ̓����蔻�� --
		for (int i{}; i < IntersectPoint::Size; ++i) {

			if (map.checkTile((int)intersectPoint.right[i].x, (int)intersectPoint.right[i].y)) {
				float hitPos = (int)(intersectPoint.right[i].x / MapInfo::MapSize) * (float)MapInfo::MapSize;

				if (intersectPoint.right[i].x >= hitPos) {
					nextPos.x = nextPos.x - fabsf(intersectPoint.right[i].x - hitPos);
					dir = Direction::Left;
					Debug::drawFormatText(100, 140, Color::Black, "%d", 1234);

					break;
				}
			}
		}

		// -- ���Ƃ̓����蔻�� --		
		for (int i{}; i < IntersectPoint::Size; ++i) {

			if (map.checkTile((int)intersectPoint.left[i].x, (int)intersectPoint.left[i].y)) {
				float hitPos = ((int)intersectPoint.left[i].x / MapInfo::MapSize + 1) * (float)MapInfo::MapSize;

				if (intersectPoint.left[i].x <= hitPos) {
					nextPos.x = nextPos.x + fabsf(intersectPoint.left[i].x - hitPos) - 1.0f;
					dir = Direction::Right;
					Debug::drawFormatText(100, 160, Color::Black, "%d", 43112);


					break;
				}
			}
		}

		return nextPos;
    }

    void Enemy::setMap(Map& _map)
    {
        map = _map;
    }
}