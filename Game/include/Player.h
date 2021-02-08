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
	/// �v���C���[�ɑ΂��Ă�SE�Ȃ�
	/// </summary>
	class PlayerAudio {
	public:
		PlayerAudio();
		~PlayerAudio();

		void playAudio(int _index);
		void stopAudio(int _index);

	private:
		std::vector<AudioSource> _audioList;
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

	private:
		void movePlayer();
		Vector2 verticalIntersect(const Vector2& _nextPos);
		Vector2 holizontalIntersect(const Vector2& _nextPos);
		void shotPlayer();
		void debug();

	private:
		Map* map;                    // �}�b�v
		BoxCollider collider;        // �R���C�_�[
		PlayerState playerState;     // �v���C���[�̈ړ����
		PlayerBody playerBody;
		PlayerAudio playerAudio;
		FrameTimer frameTime;
		bool isJump = false;         // �W�����v�ł��邩�̃t���O
		bool isGround = false;       // �n�ʂɑ������Ă��邩�̃t���O
		bool isFall = false;         // �������Ă��邩�̃t���O
		bool jumpInput = false;      // �W�����v�{�^�������͂���Ă��邩�̃t���O
		float yPower = 0.0f;
		float time = 0.f;

		AnimSprite waitImage;  // �ҋ@���Ă���摜
		AnimSprite walkImage;  // �����Ă���摜
	};
}

#endif // !PLAYER_H
