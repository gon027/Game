#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Lib.h"
#include "Actor.h"
#include "Map.h"
#include "ActorMove.h"
#include "Parameter.h"
#include "PlayerBody.h"

namespace gnGame {

	class Player;

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
	class Player : public IActor{
	public:
		Player();
		//Player(Map* _map);
		~Player() = default;

		void onStart() override;
		void onUpdate() override;

		Vector2 intersectTileMap() override;

		void setMap(Map* _map);

		// ���W�����Ƃɖ߂�
		void resetPosition();

		// �R���C�_�[���擾����
		BoxCollider& getCollider();

		PlayerBody& getPlayerBody();

	private:
		void movePlayer();
		Vector2 verticalIntersect(const Vector2& _nextPos);
		Vector2 holizontalIntersect(const Vector2& _nextPos);
		void shotPlayer();
		void debug();

	private:
		Map* map;                     // �}�b�v
		Sprite sprite;               // �摜
		BoxCollider collider;        // �R���C�_�[
		PlayerState playerState;     // �v���C���[�̈ړ����
		PlayerBody playerBody;
		bool isJump = false;
		bool isGround = false;
		bool isDamage = false;
		float invincibleTime = 0.0f;    // ���G����

		// �f�o�b�O�p
		Point pt;
	};

	// �v���C���[���ړ�������N���X
	class PlayerMove : public ActorMove {
	public:
		PlayerMove(Player* _player);
		~PlayerMove() = default;

		void moveActor() override;

		Player* player;
	};

}

#endif // !PLAYER_H
