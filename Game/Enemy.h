#ifndef ENEMY_H
#define ENEMY_H

#include "Lib.h"
#include "Actor.h"

namespace gnGame {

	class Enemy : public IActor {
	public:
		int a = 0;

	private:
		Texture tex;
		Sprite sp;
	};

}

#endif // !ENEMY_H