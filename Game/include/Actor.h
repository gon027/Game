#ifndef ACTOR_H
#define ACTOR_H

#include "Lib.h"

namespace gnGame {

	class IScene;

	/// <summary>
	/// 方向(向いている方向, 移動する方向)
	/// </summary>
	enum class Direction {
		Up,
		Down,
		Left,
		Right,
	};

	// マップとの当たり判定ようの構造体
	struct IntersectPoint {
		static const int Size = 2;

		vector<Vector2> right;
		vector<Vector2> left;
		vector<Vector2> top;
		vector<Vector2> bottom;

		IntersectPoint()
			: right(Size)
			, left(Size)
			, top(Size)
			, bottom(Size)
		{}
	};

	// キャラクターの基底クラス
	class Actor : public Object {
	public:
		Actor();
		~Actor() = default;

		virtual void onStart() = 0;
		virtual void onUpdate() = 0;

		// マップとの当たり判定
		virtual Vector2 intersectTileMap() = 0;

		bool fallScreen(float _fallBorder);

		// 初期位置を設定
		void initPosition(const Vector2& _initPos) {
			velocity = Vector2::Zero;
			this->transform.pos.setPos(_initPos);
		}

		// 加速ベクトルを取得する
		inline const Vector2& getVelocity() {
			return velocity;
		}

	protected:
		Vector2 velocity;                // 速度
		Bounds bounds;                   // バウンディングボックス
		IntersectPoint intersectPoint;   // 床との当たり判定
		bool isFlip = false;             // 画像が判定するかのフラグ
	};

}

#endif // !ACTOR_H
