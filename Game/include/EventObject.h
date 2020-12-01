#ifndef EVENTOBJECT_H
#define EVENTOBJECT_H

#include "Lib.h"

namespace gnGame {

	/// <summary>
	/// ���̃I�u�W�F�N�g�ɐG��ƁA�C�x���g�����΂���
	/// </summary>
	class EventObject : public Object{
	public:
		EventObject(const Vector2& _pos)
			: collider()
		{ 
			this->transform.pos.setPos(_pos);
		}

		virtual ~EventObject() = default;

		virtual void onStart() = 0;

		virtual void onUpdate() = 0;

		BoxCollider& getCollider() {
			return collider;
		}

	protected:
		BoxCollider collider;  // �C�x���g�I�u�W�F�N�g�̓����蔻��
	};

}

#endif // !EVENTOBJECT_H
