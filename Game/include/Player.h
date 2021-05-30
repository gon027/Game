#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Lib.h"
#include "Actor.h"
#include "Map.h"
#include "Parameter.h"
#include "PlayerBody.h"
#include "../FrameTimer.h"

namespace gnGame {

	using std::vector;

	// �v���C���[�̏��
	enum class PlayerState {
		Wait,            // �ҋ@��
		Move,         // �ړ���
		FirstJump,       // 1��ڂ̃W�����v
		Fall,            // ������
	};

	/// <summary>
	/// �v���C���[�N���X
	/// </summary>
	class Player : public Actor{
	public:
		Player();
		~Player() = default;

		void onStart() override;
		void onUpdate() override;

		Vector2 intersectTileMap() override;

		void setMap(Map* _map);

		// ���W�����Ƃɖ߂�
		void resetPosition(const Vector2& _pos);

		// �R���C�_�[���擾����
		BoxCollider& getCollider();

		PlayerBody& getPlayerBody();

		// ���S�����Ƃ��̏���
		void death();

		// ���X�|�[��
		void respawn(const Vector2& _pos);

		// ���x�Ȃǂ����Z�b�g
		void reset();

		// �ꎞ�I�ɑ���s�\�ɂ���
		void setIsMove(bool _isMove);

	private:
		void movePlayer();
		void jumpPlayer();
		Vector2 verticalIntersect(const Vector2& _nextPos);
		Vector2 holizontalIntersect(const Vector2& _nextPos);
		void shotPlayer();
		void debug();

	private:
		Map* map;                    // �}�b�v�̃|�C���^
		BoxCollider collider;        // �R���C�_�[
		PlayerState playerState;     // �v���C���[�̈ړ����
		PlayerBody playerBody;
		FrameTimer moveTime;
		FrameTimer jumpTime;
		bool isJump;                 // �W�����v�ł��邩�̃t���O
		bool isGround;               // �n�ʂɑ������Ă��邩�̃t���O
		bool isFall;                 // �������Ă��邩�̃t���O
		bool jumpInput;              // �W�����v�{�^�������͂���Ă��邩�̃t���O
		bool isMove;

		AnimSprite waitImage;  // �ҋ@���Ă���摜
		AnimSprite walkImage;  // �����Ă���摜
	};
}

#endif // !PLAYER_H
