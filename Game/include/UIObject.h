#ifndef UIOBJECT_H
#define UIOBJECT_H

#include "gnLib.h"

namespace gnGame {

	// UI‚ÌŠî’êƒNƒ‰ƒX
	class UIObject : public Object{
	public:
		virtual ~UIObject() = default;
		// virtual void onStart() = 0;
		// virtual void onUpdate() = 0;
	};

}

#endif // !UIOBJECT_H
