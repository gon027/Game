#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Lib.h"
#include "Actor.h"
#include "Map.h"
#include "Bullet.h"

namespace gnGame {

	using std::vector;

	class Camera;

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
		void onUpdate() override;

		Vector2 intersectTileMap() override;

		void setMap(Map& _map);

		// ���W�����Ƃɖ߂�
		void resetPosition();

		// �R���C�_�[���擾����
		BoxCollider& getCollider();

	private:
		void movePlayer();
		void shotPlayer();
		void debug();

	private:
		Map map;
		Sprite sprite;
		BoxCollider boxCollider;
		bool isJump = false;
		bool isGround = false;

		// �f�o�b�O�p
		Point pt;
	};

}

#endif // !PLAYER_H
