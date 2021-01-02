#include "../include/Item.h"
#include "../include/Camera.h"
#include "../include/PlayerBody.h"
#include "../include/TextureManager.h"

namespace gnGame {

	Item::Item(ItemType _itemType)
		: sprite()
		, collider()
		, itemType(_itemType)
	{
	}

	void Item::onStart()
	{
		switch (itemType)
		{
		case gnGame::ItemType::HP:
			// HP‚ª‰ñ•œ‚µ‚»‚¤‚È‰æ‘œ
			sprite.setTexture(TextureManager::getTexture("Apple"));
			break;
		case gnGame::ItemType::MP:
			// MP‚ª‰ñ•œ‚µ‚»‚¤‚È‰æ‘œ
			sprite.setTexture(TextureManager::getTexture("Apple"));
			break;
		case gnGame::ItemType::Attack:
			// UŒ‚—Í‚ªã‚ª‚è‚»‚¤‚È‚È‰æ‘œ
			sprite.setTexture(TextureManager::getTexture("Apple"));
			break;
		case gnGame::ItemType::Defence:
			// Žç”õ—Í‚ªã‚ª‚è‚»‚¤‚È‚È‰æ‘œ
			sprite.setTexture(TextureManager::getTexture("Apple"));
			break;
		case gnGame::ItemType::Speed:
			// ‘¬“x‚ªã‚ª‚è‚»‚¤‚È‰æ‘œ
			sprite.setTexture(TextureManager::getTexture("Apple"));
			break;
		default:
			// HP‚ª‰ñ•œ‚µ‚»‚¤‚È‰æ‘œ
			sprite.setTexture(TextureManager::getTexture("Apple"));
			break;
		}
	}

	void Item::onUpdate()
	{
		if (!this->isActive) {
			return;
		}

		if (!Camera::isOnScreen(transform.pos)) {
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
