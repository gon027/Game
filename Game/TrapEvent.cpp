#include "TrapEvent.h"
#include "include/Camera.h"
#include "include/TextureManager.h"
#include "include/Player.h"
#include "include/GameScene.h"

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

		this->collider.update(screen, 32.0f, 32.0f);
		trapSprite.draw(screen, { 1.0f, 1.0f }, 0.0f);
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