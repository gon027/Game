#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Lib.h"
#include "Actor.h"
#include "Map.h"

using std::vector;

namespace gnGame {

	class Camera;

	// �v���C���[�̉摜
	struct PlayerImage {
		Texture texture;
		Sprite sprite;

		PlayerImage();
		~PlayerImage() = default;
	};

	// �v���C���[�̈ړ��Ɋւ�����
	struct PlayerMoveInfo {
		bool isJump;         // �W�����v�ł��邩
		bool isSecondJump;   // 2��ڂ̃W�����v�ł��邩
		bool isGround;       // �n�ʂɒ��n���Ă��邩

		PlayerMoveInfo();
		~PlayerMoveInfo() = default;
	};

	/// <summary>
	/// �v���C���[�N���X
	/// </summary>
	class Player : public IActor{
	public:
		Player();
		~Player() = default;

		void onStart() override;
		void onUpdate(float _deltaTime) override;

		Vector2 intersectTileMap() override;

		void setMap(Map& _map);

		// ���W�����Ƃɖ߂�
		void resetPosition();

		void debug();

	private:
		Map map;
		
		bool isJump = false;
		bool isGround = false;

		float aaaa = 0.0f;

		// �f�o�b�O�p
		PlayerImage pImage;
		Point pt;
	};

}

#endif // !PLAYER_H
