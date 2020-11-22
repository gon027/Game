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

	class SceneManager;

	class Game : public IScene{
	public:
		Game();
		Game(SceneManager* _sceneManager);
		~Game();

		void onStart() override;
		void onUpdate() override;
		void onFinal() override;

	private:
		SceneManager* sceneManager;
		Fps fps;
		Map* map;
		Player player;
		BackGround bg;
	};
}

#endif // !GAME_H
