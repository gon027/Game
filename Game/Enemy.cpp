#include "Enemy.h"
#include "Camera.h"

namespace gnGame {

	Enemy::Enemy(Camera* _camera, Map& _map)
		: camera(_camera)
		, map(_map)
		, pos()
		, velocity()
		, isJump(false)
		, isGround(false)
		, intersectPoint()
		, tex("Image/Enemy.png")
		, sp(tex)
	{
	}

	void Enemy::onStart()
	{
		// -- 座標初期化 --
		pos.setPos(75, 350);

		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(32, 32);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	void Enemy::onUpdate()
	{

		velocity.y = 1.0f;

		intersectTileMap();

		sp.draw();
	}

	void Enemy::setMap(Map& _map)
	{
		map = _map;
	}

	void Enemy::intersectTileMap()
	{
		// ----- 移動判定 -----

		auto nextPos = pos + velocity;

		// 判定を行う座標を更新
		float offX{ bounds.center.x / 4.0f - 1.0f };
		float offY{ bounds.center.y / 4.0f - 1.0f };

		// 上下判定用のに判定ボックス更新
		bounds.minPos.setPos(pos.x - bounds.center.x, nextPos.y - bounds.center.y);
		bounds.maxPos.setPos(pos.x + bounds.center.x, nextPos.y + bounds.center.y);

		// -- 下 --
		intersectPoint.bottom[0] = Vector2{ bounds.minPos.x + offX, bounds.maxPos.y + 1.0f };
		intersectPoint.bottom[1] = Vector2{ bounds.maxPos.x - offX, bounds.maxPos.y + 1.0f };

		// -- 上 --
		intersectPoint.top[0] = Vector2{ bounds.minPos.x + offX, bounds.minPos.y - 1.0f };
		intersectPoint.top[1] = Vector2{ bounds.maxPos.x - offX, bounds.minPos.y - 1.0f };

		// -- 上との当たり判定 --
		for (int i{}; i < IntersectPoints::Size; ++i) {

			if (map.checkTile((int)intersectPoint.top[i].x, (int)intersectPoint.top[i].y)) {

				// あたった場所を求める
				auto hitPos = ((int)intersectPoint.top[i].y / 32 + 1) * 32.0f;

				if (intersectPoint.top[i].y <= hitPos) {
					nextPos.y = nextPos.y + fabsf(intersectPoint.top[i].y - hitPos) - 1.0f;

					break;
				}
			}
		}

		// -- 下との当たり判定 --
		for (int i{}; i < IntersectPoints::Size; ++i) {

			if (map.checkTile((int)intersectPoint.bottom[i].x, (int)intersectPoint.bottom[i].y)) {

				// あたった場所を求める
				auto hitPos = (int)(intersectPoint.bottom[i].y / 32) * 32.0f;

				if (intersectPoint.bottom[i].y >= hitPos) {
					nextPos.y = nextPos.y - fabsf(intersectPoint.bottom[i].y - hitPos) + 1.0f;

					// 地面についているとき
					isGround = true;

					break;
				}
			}
			else {
				// 下にマップチップがないとき
				isGround = false;
			}
		}

		// 左右判定用に判定ボックス更新
		bounds.minPos.setPos(nextPos.x - bounds.center.x, pos.y - bounds.center.y);
		bounds.maxPos.setPos(nextPos.x + bounds.center.x, pos.y + bounds.center.y);

		// -- 右 --
		intersectPoint.right[0] = Vector2{ bounds.maxPos.x , bounds.minPos.y + offY };
		intersectPoint.right[1] = Vector2{ bounds.maxPos.x , bounds.maxPos.y - offY };

		// -- 左 --
		intersectPoint.left[0] = Vector2{ bounds.minPos.x - 1.0f, bounds.minPos.y + offY };
		intersectPoint.left[1] = Vector2{ bounds.minPos.x - 1.0f, bounds.maxPos.y - offY };


		// -- 右との当たり判定 --
		for (int i{}; i < IntersectPoints::Size; ++i) {

			if (map.checkTile((int)intersectPoint.right[i].x, (int)intersectPoint.right[i].y)) {
				float hitPos = (int)(intersectPoint.right[i].x / 32) * 32.0f;

				if (intersectPoint.right[i].x >= hitPos) {
					nextPos.x = nextPos.x - fabsf(intersectPoint.right[i].x - hitPos) + 1.0f;

					break;
				}
			}
		}

		// -- 左との当たり判定 --		
		for (int i{}; i < IntersectPoints::Size; ++i) {

			if (map.checkTile((int)intersectPoint.left[i].x, (int)intersectPoint.left[i].y)) {
				float hitPos = ((int)intersectPoint.left[i].x / 32 + 1) * 32.0f;

				if (intersectPoint.left[i].x <= hitPos) {
					nextPos.x = nextPos.x + fabsf(intersectPoint.left[i].x - hitPos) - 1.0f;
					break;
				}
			}
		}

		// ----- 座標更新 -----
		pos = nextPos;                      // 座標を更新
		auto screen = camera->toScreenPos(pos);  // 座標をスクリーン座標へと変換
		sp.setPos(screen);       // プレイヤーの画像の座標を更新
	}

}