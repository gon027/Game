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
		Player(Camera* camera, Map& _map);
		~Player() = default;

		void onStart() override;
		void onUpdate() override;

		void setMap(Map& _map);

		// �����蔻��
		Vector2 intersectTileMap() override;

		// ���W�����Ƃɖ߂�
		void resetPosition();

		void debug();

	private:
		Camera* camera;
		Map map;
		
		bool isJump = false;
		bool isGround = false;

		// �f�o�b�O�p
		PlayerImage pImage;
		Point pt;
	};

}

#endif // !PLAYER_H
