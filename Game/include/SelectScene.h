#ifndef SELECTSCENE_H
#define SELECTSCENE_H

#include "Lib.h"
#include "Scene.h"

namespace gnGame {

	class SceneManager;

	class SelectSceneUI {
	public:
		SelectSceneUI();
		~SelectSceneUI();

		void onStart();

		void onUpdate();

		void onFinal();

	private:
		Sprite backGround;
	};

	class SelectScene final : public IScene {
	public:
		SelectScene(SceneManager* _sceneManager);
		~SelectScene() = default;

		void onStart() override;

		void onUpdate() override;

		void onFinal() override;

	private:
		SceneManager* sceneManager;
		SelectSceneUI selectSceneUI;
	};
}

#endif // !SELECTSCENE_H