#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "Lib.h"
#include "Scene.h"
#include "Player.h"
#include "BackGround.h"
#include "Camera.h"
#include "Map.h"
#include "Fps.h"

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
		MapList mapList;
		int currentMap{ 0 };
	};
}

#endif // !GAME_H
