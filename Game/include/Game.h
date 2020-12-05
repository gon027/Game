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
#include "StageEvent.h"

namespace gnGame {

	using MapList = std::vector<std::string>;

	class Game : public IScene{
	public:
		Game();
		~Game();

		void onStart() override;
		void onUpdate() override;
		void onFinal() override;

		// プレイヤーを取得
		Player* getPlayer();

		// マップを取得
		Map* getMap();

		// マップをリセットする
		void resetMap();

		// 次のステージに繊維
		void nextStage();

	private:
		Fps fps;
		Map* map;
		Player player;
		BackGround bg;
		int currentMap{ 0 };
		MapList mapList;
	};
}

#endif // !GAME_H
