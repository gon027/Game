#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include "Lib.h"

using std::string;

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
		IActor() 
			: name()
			, pos()
			, velocity()
			, bounds()
			, intersectPoint()
		{}

		~IActor() = default;

		virtual void onStart() = 0;
		virtual void onUpdate(float _deltaTime) = 0;

		// �}�b�v�Ƃ̓����蔻��
		virtual Vector2 intersectTileMap() = 0;

		// �I�u�W�F�N�g�̖��O���擾����
		inline const string& getName() {
			return name;
		}

		// ���W���擾����
		inline const Vector2& getPos() {
			return pos;
		}

		// �����x�N�g�����擾����
		inline const Vector2& getVelocity() {
			return velocity;
		}

	protected:
		string name;                     // ���g�̃I�u�W�F�N�g�̖��O
		Vector2 pos;                     // ���W
		Vector2 velocity;                // ���x
		Bounds bounds;                   // �o�E���f�B���O�{�b�N�X
		IntersectPoint intersectPoint;   // ���Ƃ̓����蔻��
	};

}

#endif // !ACTOR_H
