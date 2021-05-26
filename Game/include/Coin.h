#ifndef COIN_H
#define COIN_H

#include "Item.h"

namespace gnGame {

	class Coin : public Item {
	public:
		Coin(const Vector2& _pos);
		~Coin() = default;

		void onStart() override;

		void onUpdate() override;

		// プレイヤーにアイテム効果を渡す
		void onCollision(class Player& _player) override;

		// コライダーを取得
		ICollider& getCollider() override;

	public:
		CircleCollider collider;
	};
}

#endif // !COIN_H