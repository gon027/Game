#ifndef ACTOR_H
#define ACTOR_H

#include "Lib.h"
#include "GameObject.h"
#include "ActorBody.h"

namespace gnGame {

	class IScene;

	/// <summary>
	/// ����(�����Ă������, �ړ��������)
	/// </summary>
	enum class Direction {
		Up,
		Down,
		Left,
		Right,
	};

	// �}�b�v�Ƃ̓����蔻��悤�̍\����
	struct IntersectPoint {
		static const int Size = 2;

		vector<Vector2> right;
		vector<Vector2> left;
		vector<Vector2> top;
		vector<Vector2> bottom;

		IntersectPoint()
			: right(Size)
			, left(Size)
			, top(Size)
			, bottom(Size)
		{}
	};

	// �L�����N�^�[�̊��N���X
	class Actor : public GameObject {
	public:
		Actor();
		~Actor() = default;

		// �}�b�v�Ƃ̓����蔻��
		virtual Vector2 intersectTileMap() = 0;

		bool fallScreen(float _fallBorder);

		// �����ʒu��ݒ�
		void initPosition(const Vector2& _initPos) {
			velocity = Vector2::Zero;
			this->transform.pos.setPos(_initPos);
		}

		// �����x�N�g�����擾����
		inline const Vector2& getVelocity() {
			return velocity;
		}

		// �̗͂Ȃǂ̏����擾����
		virtual ActorBody& getActorBody() = 0;

		virtual BoxCollider& getCollider() = 0;

	protected:
		Vector2 velocity;                // ���x
		Bounds bounds;                   // �o�E���f�B���O�{�b�N�X
		IntersectPoint intersectPoint;   // ���Ƃ̓����蔻��
		bool isFlip = false;             // �摜�����肷�邩�̃t���O
	};

}

#endif // !ACTOR_H
