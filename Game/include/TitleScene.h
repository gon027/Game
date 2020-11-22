#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "gnLib.h"
#include "Scene.h"

namespace gnGame {

	class SceneManager;

	class TitleScene final : public IScene {
	public:
		TitleScene(SceneManager* _sceneManager);
		~TitleScene() = default;

		void onStart() override;

		void onUpdate() override;

		void onFinal() override;

	private:
		SceneManager* sceneManager;
	};
}

#endif // !TITLESCENE_H