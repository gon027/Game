#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Lib.h"
#include "Actor.h"
#include "Map.h"
#include "Parameter.h"

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

		void appryDamage(int _damage);

		// �R���C�_�[���擾����
		BoxCollider& getCollider();

	private:
		void movePlayer();
		Vector2 verticalIntersect(const Vector2& _nextPos);
		Vector2 holizontalIntersect(const Vector2& _nextPos);
		void shotPlayer();
		void debug();


	private:
		Map map;                     // �}�b�v
		Sprite sprite;               // �摜
		BoxCollider collider;        // �R���C�_�[
		PlayerState playerState;     // �v���C���[�̈ړ����
		ActorParameter parameter;    // �v���C���[�̃p�����[�^
		bool isJump = false;
		bool isGround = false;

		// �f�o�b�O�p
		Point pt;
	};

}

#endif // !PLAYER_H
