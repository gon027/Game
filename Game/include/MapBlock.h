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

		MapTile getMapTiel();
		
		void setPos(const Vector2& _pos);
		
		Vector2 getPos();
		
		void setTexture(TextureSPtr& _texture);
		
		void setTextureRect(const TextureRect& _tRect);

		virtual void draw() = 0;

		virtual ICollider* getCollider() = 0;
		
	protected:
		MapTile mapTile;        // ブロックのタイプ
		Vector2 pos;            // 座標
		TextureRect tRect;      // テクスチャの描画範囲
		Sprite mapSprite;       // マップのスプライト
	};

	/// <summary>
	/// 空のブロック
	/// </summary>
	struct EmptyBlock : public MapBlock {
		EmptyBlock();
		~EmptyBlock() = default;

		void draw() override;
		ICollider* getCollider() override;
	};

	/// <summary>
	/// ブロックの上に乗れるブロック
	/// </summary>
	struct NomalBlock : public MapBlock {
		NomalBlock();
		~NomalBlock() = default;

		void draw() override;
		ICollider* getCollider() override;
	};

	/// <summary>
	/// すり抜けるブロック
	/// </summary>
	struct SlidingBlock : public MapBlock {
		SlidingBlock();
		~SlidingBlock() = default;

		void draw() override;
		ICollider* getCollider() override;
	};


	MapBlock* createMapBlock(MapTile _mapTile);
}

#endif // !MAPBLOCK_H