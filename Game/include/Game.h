#ifndef GAME_H
#define GAME_H

#include "Lib.h"
#include "Scene.h"
#include "Camera.h"
#include "Map.h"
#include "Player.h"
#include "Fps.h"
#include "BackGround.h"
#include "../TextEvent.h"

namespace gnGame {

	class Game : public IScene{
	public:
		Game();
		~Game();

		void onStart() override;
		void onUpdate() override;
		void onFinal() override;

	private:
		Fps fps;
		Map* map;
		Player player;
		BackGround bg;
		TextEvent te;
	};
}

#endif // !GAME_H
