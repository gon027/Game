#include "TrapEvent.h"
#include "include/Camera.h"
#include "include/TextureManager.h"

namespace gnGame {

	TrapEvent::TrapEvent(const Vector2& _pos, GameScene* _gameScene)
		: EventObject(_pos, _gameScene)
		, collider({ {} })
		, trapSprite()
	{
		trapSprite.setTexture(TextureManager::getTexture("Needle"));
	}

	void TrapEvent::onUpdate()
	{
		auto screen = Camera::toScreenPos(this->transform.pos);

		trapSprite.draw(screen, { 1.0f, 1.0f }, 0.0f);
	}

	void TrapEvent::onEvent()
	{

	}

	ICollider& TrapEvent::getCollider()
	{
		return collider;
	}







	TriangleCollider::TriangleCollider(std::initializer_list<Vector2> _pointList)
	{
	}

	ColliderType TriangleCollider::getType()
	{
		return ColliderType();
	}

	bool TriangleCollider::isHitTest(const BoxCollider& _collider)
	{
		return false;
	}

	bool TriangleCollider::isHitTest(const CircleCollider& _collider)
	{
		return false;
	}

	bool TriangleCollider::isHitTest(const TriangleCollider& _collider)
	{
		return false;
	}

	void TriangleCollider::update(const Vector2& _v)
	{
	}

}