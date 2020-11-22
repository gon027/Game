#ifndef SELECTSCENE_H
#define SELECTSCENE_H

#include "gnLib.h"
#include "Scene.h"

namespace gnGame {

	class SceneManager;

	class SelectScene final : public IScene {
	public:
		SelectScene(SceneManager* _sceneManager);
		~SelectScene() = default;

		void onStart() override;

		void onUpdate() override;

		void onFinal() override;

	private:
		SceneManager* sceneManager;
	};
}

#endif // !SELECTSCENE_H