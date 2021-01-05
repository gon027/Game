#ifndef MAPBLOCK_H
#define MAPBLOCK_H

#include "Lib.h"

namespace gnGame {

	// マップのタイル
	enum class MapTile {
		NONE = 0,
		BLOCK = 1,
		OBJECT = 10,
	};

	/// <summary>
	/// ブロックの基底となる構造体
	/// </summary>
	struct MapBlock {
		MapBlock();
		virtual ~MapBlock() = default;

		void setMapTile(MapTile _mapTile);

		const MapTile getMapTile();
		
		void setPos(const Vector2& _pos);
		
		const Vector2& getPos();
		
		void setTexture(TextureSPtr& _texture);
		
		void setTextureRect(const TextureRect& _tRect);

		virtual const BoxCollider& getCollider() const;

		virtual void draw() = 0;

	protected:
		MapTile mapTile;        // ブロックのタイプ
		Vector2 pos;            // 座標
		TextureRect tRect;      // テクスチャの描画範囲
		Sprite mapSprite;       // マップのスプライト
		BoxCollider collider;   // ブロックのコライダー
	};

	/// <summary>
	/// 空のブロック
	/// </summary>
	struct EmptyBlock : public MapBlock {
		EmptyBlock();
		~EmptyBlock() = default;

		void draw() override;
	};

	/// <summary>
	/// ブロックの上に乗れるブロック
	/// </summary>
	struct NomalBlock : public MapBlock {
		NomalBlock();
		~NomalBlock() = default;

		void draw() override;
	};

	/// <summary>
	/// すり抜けるブロック
	/// </summary>
	struct SlidingBlock : public MapBlock {
		SlidingBlock();
		~SlidingBlock() = default;

		void draw() override;
	};

	/// <summary>
	/// 壊せるブロック
	/// </summary>
	struct StoneBlock : public MapBlock {
		StoneBlock();
		~StoneBlock() = default;

		void draw() override;
	};

	MapBlock* createMapBlock(MapTile _mapTile);
}

#endif // !MAPBLOCK_H