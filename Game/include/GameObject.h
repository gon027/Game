#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "gnLib.h"

namespace gnLib {

	class GameObject : public Object {
	public:
		GameObject() : Object() {}
		virtual ~GameObject() = default;

		// Å‰‚ÉŒÄ‚Î‚ê‚éŠÖ”
		virtual void onStart() = 0;

		// XV‚ÉŒÄ‚Î‚ê‚éŠÖ”
		virtual void onUpdate() = 0;

		// •`‰æŠÖ”
		virtual void onDraw() = 0;
	};

}

#endif // !GAMEOBJECT_H
