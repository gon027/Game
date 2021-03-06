#include "../include/MapBlock.h"
#include "../include/TextureManager.h"

namespace gnGame {
	MapBlock::MapBlock()
		: mapTile(MapTile::NONE)
		, pos()
		, tRect()
		, mapSprite()
	{
	}

	void MapBlock::setMapTile(MapTile _mapTile)
	{
		mapTile = _mapTile;
	}

	const MapTile MapBlock::getMapTile()
	{
		return mapTile;
	}

	void MapBlock::setPos(const Vector2& _pos)
	{
		pos = _pos;
	}

	const Vector2& MapBlock::getPos()
	{
		return pos;
	}

	void MapBlock::setTexture(TextureSPtr& _texture)
	{
		mapSprite.setTexture(_texture);
	}

	void MapBlock::setTextureRect(const TextureRect& _tRect)
	{
		tRect = _tRect;
	}

	const BoxCollider& MapBlock::getCollider() const
	{
		return collider;
	}

	EmptyBlock::EmptyBlock()
		: MapBlock()
	{
	}

	void EmptyBlock::draw()
	{
	}

	NomalBlock::NomalBlock()
		: MapBlock()
	{
		this->mapSprite.setTexture(TextureManager::getTexture("MapChip"));
	}

	void NomalBlock::draw()
	{
		this->mapSprite.draw(tRect, pos, Vector2::One, 0.0f);
	}

	SlidingBlock::SlidingBlock()
		: MapBlock()
	{
		this->mapSprite.setTexture(TextureManager::getTexture("floor"));
	}

	void SlidingBlock::draw()
	{
		this->mapSprite.draw(pos, Vector2::One, 0.0f);
	}

	StoneBlock::StoneBlock()
		: MapBlock()
	{
		this->mapSprite.setTexture(TextureManager::getTexture("floor"));
	}

	void StoneBlock::draw()
	{
		collider.update(pos, 32.0f, 32.0f);
		this->mapSprite.draw(pos, Vector2::One, 0.0f);
	}

	MapBlock* createMapBlock(MapTile _mapTile) {
		MapBlock* result = nullptr;

		switch (_mapTile)
		{
		case gnGame::MapTile::NONE:
			result = new EmptyBlock();
			result->setMapTile(MapTile::NONE);
			return result;
		case gnGame::MapTile::BLOCK:
			result = new NomalBlock();
			result->setMapTile(MapTile::BLOCK);
			return result;
		case gnGame::MapTile::OBJECT:
			result = new SlidingBlock();
			result->setMapTile(MapTile::OBJECT);
			return result;
		default:
			result = new NomalBlock();
			result->setMapTile(MapTile::BLOCK);
			return result;
		}

		return nullptr;
	}
}