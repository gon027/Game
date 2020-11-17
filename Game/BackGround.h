#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Lib.h"

namespace gnGame {

	class BackGround {
	public:
		BackGround(const Vector2& _pos);
		~BackGround() = default;

		void setTexture();
		void draw();

	private:
		Vector2 pos;
		Sprite backGround;
	};

}

#endif // !BACKGROUND_H
