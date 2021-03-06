#ifndef UIOBJECT_H
#define UIOBJECT_H

#include "gnLib.h"

namespace gnGame {

	// UIの基底クラス
	class UIObject {
	public:
		virtual ~UIObject() = default;
		virtual void OnDraw() = 0;
	};

}

#endif // !UIOBJECT_H
