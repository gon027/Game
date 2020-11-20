#ifndef ACTOR_H
#define ACTOR_H

#include "Lib.h"

namespace gnGame {

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

		virtual bool isOnScreen();

		// �}�b�v�Ƃ̓����蔻��
		virtual Vector2 intersectTileMap() = 0;

		// �����x�N�g�����擾����
		inline const Vector2& getVelocity() {
			return velocity;
		}

	protected:
		Vector2 velocity;                // ���x
		Bounds bounds;                   // �o�E���f�B���O�{�b�N�X
		IntersectPoint intersectPoint;   // ���Ƃ̓����蔻��
	};

}

#endif // !ACTOR_H
