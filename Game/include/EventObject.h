#ifndef EVENTOBJECT_H
#define EVENTOBJECT_H

#include "Lib.h"

namespace gnGame {

	class EventObject : public Object{
	public:
		EventObject();
		~EventObject() = default;

		BoxCollider& getCollider();

	private:
		BoxCollider collider;
	};

}

#endif // !EVENTOBJECT_H
