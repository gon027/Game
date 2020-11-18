#ifndef GAME_H
#define GAME_H

#include "Lib.h"
#include "Scene.h"
#include "Camera.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Fps.h"
#include "BackGround.h"
#include "EnemyManager.h"

namespace gnGame {

	class Game : public IScene{
	public:
		Game();
		~Game();

		void onStart() override;
		void onUpdate(float _deltaTime) override;
		void onFinal() override;

	private:
		Map* map;
		Player player;
		EnemyPtr enemy;
		
		BackGround bg;
		Fps fps;
	};
}

#endif // !GAME_H
