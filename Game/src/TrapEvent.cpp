#include "../include/TrapEvent.h"
#include "../include/Camera.h"
#include "../include/TextureManager.h"
#include "../include/Player.h"
#include "../include/GameScene.h"

namespace gnGame {

	TrapEvent::TrapEvent(const Vector2& _pos, GameScene* _gameScene)
		: EventObject(_pos, _gameScene)
		, collider()
		, trapSprite()
	{
		trapSprite.setTexture(TextureManager::getTexture("Needle"));
	}

	void TrapEvent::onUpdate()
	{
		auto screen = Camera::toScreenPos(this->transform.pos);

		this->collider.update(screen + Vector2{16.0f, 16.0f}, 24.0f, 24.0f);
		trapSprite.draw(screen, Vector2::One, 0.0f, false);
	}

	void TrapEvent::onEvent()
	{
		auto player = gameScene->getPlayer();
		player->death();
	}

	ICollider& TrapEvent::getCollider()
	{
		return collider;
	}
}