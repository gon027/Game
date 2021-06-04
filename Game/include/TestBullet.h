#pragma once

#include "Lib.h"
#include "GameObject.h"

namespace gnGame {

	class TestBullet : public GameObject {
	public:
		TestBullet(const Vector2& _pos, const Vector2& _velocity);
		~TestBullet() = default;

		void onStart() override;

		void onUpdate() override;

	private:
		Sprite sprite;
		Vector2 velocity;
	};
}