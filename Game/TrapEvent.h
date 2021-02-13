#ifndef TRAPEVENT_H
#define TRAPEVENT_H

#include <vector>
#include "include/Lib.h"
#include "include/EventObject.h"


namespace gnLib {
	class TriangleCollider : public ICollider {
	public:
		TriangleCollider(std::initializer_list<Vector2> _pointList);
		~TriangleCollider() = default;

		virtual ColliderType getType() override;

		bool isHitTest(const BoxCollider& _collider) override;
		bool isHitTest(const CircleCollider& _collider) override;
		bool isHitTest(const TriangleCollider& _collider);

		void update(const Vector2& _v);

	private:
		std::vector<Vector2> pointList;
		Vector2 pos;
	};
}

namespace gnGame {
	class TrapEvent : public EventObject {
	public:
		TrapEvent(const Vector2& _pos, GameScene* _gameScene);
		~TrapEvent() = default;

		void onUpdate() override;
		void onEvent() override;

		ICollider& getCollider() override;

	private:
		TriangleCollider collider;
		Sprite trapSprite;
	};
}

#endif // !TRAPEVENT_H