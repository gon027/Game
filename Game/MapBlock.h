#ifndef MAPBLOCK_H
#define MAPBLOCK_H

#include "include/Lib.h"

namespace gnGame {

	// �}�b�v�̃^�C��
	enum class MapTile {
		NONE = 0,
		BLOCK = 1,
		OBJECT = 2,
	};

	/// <summary>
	/// �u���b�N�̊��ƂȂ�\����
	/// </summary>
	struct MapBlock {
		MapBlock();
		virtual ~MapBlock() = default;

		virtual void setMapTile(MapTile _mapTile);
		virtual MapTile getMapTiel();

		virtual void setPos(const Vector2& _pos);

		virtual void setTextureRect(const TextureRect& _tRect);

		virtual void draw() = 0;

		virtual ICollider* getCollider() = 0;
		
	protected:
		MapTile mapTile;        // �u���b�N�̃^�C�v
		Vector2 pos;            // ���W
		TextureRect tRect;      // �e�N�X�`���̕`��͈�
		Sprite mapSprite;       // �}�b�v�̃X�v���C�g
	};

	/// <summary>
	/// �u���b�N�̏�ɏ���u���b�N
	/// </summary>
	struct NomalBlock : public MapBlock {
		NomalBlock();
		~NomalBlock() = default;

		void draw() override;
		ICollider* getCollider() override;
	};

	/// <summary>
	/// ���蔲����u���b�N
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