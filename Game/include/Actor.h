#ifndef ACTOR_H
#define ACTOR_H

#include "Lib.h"

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
	class IActor : public Object {
	public:
		IActor();
		~IActor() = default;

		virtual void onStart() = 0;
		virtual void onUpdate() = 0;

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

	protected:
		Vector2 velocity;                // ���x
		Bounds bounds;                   // �o�E���f�B���O�{�b�N�X
		IntersectPoint intersectPoint;   // ���Ƃ̓����蔻��
		bool isFlip = false;             // �摜�����肷�邩�̃t���O
	};

}

#endif // !ACTOR_H
