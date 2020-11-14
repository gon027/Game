#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include "Lib.h"

using std::string;

namespace gnGame {

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
	class IActor : public Object {
	public:
		IActor() 
			: name()
			, pos()
			, velocity()
			, bounds()
			, intersectPoint()
		{}

		~IActor() = default;

		virtual void onStart() = 0;
		virtual void onUpdate(float _deltaTime) = 0;

		// マップとの当たり判定
		virtual Vector2 intersectTileMap() = 0;

		// オブジェクトの名前を取得する
		inline const string& getName() {
			return name;
		}

		// 座標を取得する
		inline const Vector2& getPos() {
			return pos;
		}

		// 加速ベクトルを取得する
		inline const Vector2& getVelocity() {
			return velocity;
		}

	protected:
		string name;                     // 自身のオブジェクトの名前
		Vector2 pos;                     // 座標
		Vector2 velocity;                // 速度
		Bounds bounds;                   // バウンディングボックス
		IntersectPoint intersectPoint;   // 床との当たり判定
	};

}

#endif // !ACTOR_H
