#ifndef UIOBJECT_H
#define UIOBJECT_H

#include "gnLib.h"

namespace gnGame {

	// UI�̊��N���X
	class UIObject {
	public:
		virtual ~UIObject() = default;

		virtual void OnDraw() = 0;
	};

}

#endif // !UIOBJECT_H
