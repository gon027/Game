#ifndef SELECTSCENE_H
#define SELECTSCENE_H

#include "Scene.h"
#include "BackGround.h"

namespace gnGame {

	class SceneManager;

	// セレクトシーンのUIクラス
	class SelectSceneUI {
	public:
		SelectSceneUI();
		~SelectSceneUI();

		void onStart();

		void onUpdate();

		void onFinal();

		// プレイヤーからのステージの操作を受け付ける
		void stageSelect();

	private:
		Sprite backGround;            // 背景
		Sprite number;                // ステージ画像
		Sprite frame;                 // フレーム
		TextureRegion textureRegion;  // ステージ番号の画像の区間を分割した配列
	};

	// セレクトシーンクラス
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