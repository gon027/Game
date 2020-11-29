#ifndef EVENTOBJECT_H
#define EVENTOBJECT_H

#include "Lib.h"

namespace gnGame {

	/// <summary>
	/// このオブジェクトに触ると、イベントが発火する
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

		virtual void onEvent() = 0;

		BoxCollider& getCollider() {
			return collider;
		}

	protected:
		BoxCollider collider;
	};

}

#endif // !EVENTOBJECT_H
