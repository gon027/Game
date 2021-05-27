#include "Coin.h"
#include "Camera.h"
#include "TextureManager.h"
#include "CoinScoreManager.h"

namespace gnGame {

	Coin::Coin(const Vector2& _pos)
		: Item()
		, collider()
	{
		this->transform.setPos(_pos);
		this->sprite.setTexture(TextureManager::getTexture("Coin"));
	}

	void Coin::onStart()
	{
		
	}

	void Coin::onUpdate()
	{
		auto screen = Camera::toScreenPos(this->transform.pos);

		// 画像が16.0f分ずれているので、コライダーの一も16.0fずらす
		collider.update(screen + Vector2{ 8.0f, 8.0f }, 24.0f);
		sprite.draw(screen, Vector2::One, 0.0f, false);
	}

	void Coin::onCollision(Player& _player)
	{
		CoinScoreManager::getIns()->addScore();
	}

	ICollider& gnGame::Coin::getCollider()
	{
		return collider;
	}

}