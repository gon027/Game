#ifndef GAME_H
#define GAME_H

#include "Lib.h"
#include "Scene.h"
#include "Camera.h"
#include "Map.h"
#include "Player.h"
#include "Fps.h"
#include "BackGround.h"

namespace gnGame {

	class StageObject {
	public:
		Map* getMap();
		Player* getPlayer();

	private:
		Map map;
		Player player;
	};

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
	};
}

#endif // !GAME_H
