#ifndef GAME_H
#define GAME_H

#include "Lib.h"
#include "Scene.h"

namespace gnGame {

	class Game : public IScene{
	public:
		Game() = default;
		~Game() = default;

		void onStart() override;
		void onUpdate() override;
	};
}


#endif // !GAME_H
