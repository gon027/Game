#ifndef MAPBLOCK_H
#define MAPBLOCK_H

#include "Lib.h"

namespace gnGame {

	// �}�b�v�̃^�C��
	enum class MapTile {
		NONE = 0,
		BLOCK = 1,
		OBJECT = 10,
	};

	/// <summary>
	/// �u���b�N�̊��ƂȂ�\����
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
		MapTile mapTile;        // �u���b�N�̃^�C�v
		Vector2 pos;            // ���W
		TextureRect tRect;      // �e�N�X�`���̕`��͈�
		Sprite mapSprite;       // �}�b�v�̃X�v���C�g
		BoxCollider collider;   // �u���b�N�̃R���C�_�[
	};

	/// <summary>
	/// ��̃u���b�N
	/// </summary>
	struct EmptyBlock : public MapBlock {
		EmptyBlock();
		~EmptyBlock() = default;

		void draw() override;
	};

	/// <summary>
	/// �u���b�N�̏�ɏ���u���b�N
	/// </summary>
	struct NomalBlock : public MapBlock {
		NomalBlock();
		~NomalBlock() = default;

		void draw() override;
	};

	/// <summary>
	/// ���蔲����u���b�N
	/// </summary>
	struct SlidingBlock : public MapBlock {
		SlidingBlock();
		~SlidingBlock() = default;

		void draw() override;
	};

	/// <summary>
	/// �󂹂�u���b�N
	/// </summary>
	struct StoneBlock : public MapBlock {
		StoneBlock();
		~StoneBlock() = default;

		void draw() override;
	};

	MapBlock* createMapBlock(MapTile _mapTile);
}

#endif // !MAPBLOCK_H