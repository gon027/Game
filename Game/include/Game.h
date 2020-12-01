#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "Lib.h"
#include "Scene.h"
#include "Camera.h"
#include "Map.h"
#include "Player.h"
#include "Fps.h"
#include "BackGround.h"
#include "../TextEvent.h"

namespace gnGame {

	using MapList = std::vector<std::string>;

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
		int currentMap{ 0 };
		MapList mapList;
	};
}

#endif // !GAME_H
