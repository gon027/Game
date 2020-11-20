#include "Item.h"
#include "include/Camera.h"
#include "include/TextureManager.h"

namespace gnGame {

	Item::Item()
		: sprite()
		, collider()
	{
	}

	void Item::onStart()
	{
		sprite.setTexture(TextureManager::getTexture("Apple"));
		this->transform.pos.setPos(1000.f, 500.f);
	}

	void Item::onUpdate()
	{

		if (!this->isActive) {
			return;
		}

		if (!this->isOnScreen()) {
			return;
		}

		auto screen = Camera::toScreenPos(this->transform.pos);
		collider.update(screen, 32.0f, 32.0f);
		sprite.draw(screen, Vector2::One, 0.0f);
	}

	bool Item::isOnScreen()
	{
		auto minScrenn = Camera::minScreenPos();
		auto maxScreen = Camera::maxScreenPos();

		return transform.pos.x >= minScrenn.x && transform.pos.x <= maxScreen.x
			&& transform.pos.y >= minScrenn.y && transform.pos.y <= maxScreen.y;
	}

	void Item::setEffect(Player& _player)
	{
	}

	BoxCollider& Item::getCollider()
	{
		return collider;
	}
}
