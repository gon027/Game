#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Lib.h"
#include "Scene.h"

namespace gnGame {

	class SceneManager;

	class GameScene final : public IScene {
	public:
		GameScene(SceneManager* _sceneManager);
		~GameScene() = default;

		void onStart() override;

		void onUpdate() override;

		void onFinal() override;

	private:
		SceneManager* sceneManager;
	};
}

#endif // !GAMESCENE_H