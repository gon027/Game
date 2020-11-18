#ifndef BULLET_H
#define BULLET_H

#include "Lib.h"

namespace gnGame {
	class Bullet : public Object {
	public:
		Bullet(const Vector2& _pos, const Vector2& _velocity);
		~Bullet() = default;

		void onStart();

		void onUpdate();

	private:
		Vector2 velocity;
		Rect rect;
	};
}

#endif // !BULLET_H
