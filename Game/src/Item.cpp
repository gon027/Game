#include "../include/Item.h"
#include "../include/Camera.h"
#include "../include/PlayerBody.h"
#include "../include/TextureManager.h"

namespace gnGame {

	Item::Item()
		: sprite()
		, collider()
	{
	}

	void Item::onStart()
	{
		sprite.setTexture(TextureManager::getTexture("Apple"));
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

	void Item::setEffect(PlayerBody& _player)
	{
		switch (itemType)
		{
		case gnGame::ItemType::HP:
			_player.setHP(20.f);
			break;
		case gnGame::ItemType::MP:
			_player.subMp(20.f);
			break;
		case gnGame::ItemType::Attack:
			_player.setAttack(20.f);
			break;
		case gnGame::ItemType::Defence:
			_player.setDefence(20.f);
			break;
		case gnGame::ItemType::Speed:
			_player.setSpeed(20.f);
			break;
		default:
			_player.setHP(500.f);
			break;
		}
	}

	BoxCollider& Item::getCollider()
	{
		return collider;
	}
	const ItemType Item::getItemType()
	{
		return itemType;
	}
}
