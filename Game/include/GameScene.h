#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <vector>
#include <string>
#include "Lib.h"
#include "Scene.h"
#include "Player.h"
#include "BackGround.h"
#include "Stage.h"

namespace gnGame {

	class SceneManager;
	class Map;

	class GameSceneUI {
	public:
		GameSceneUI();
		~GameSceneUI() = default;

		void onStart();

		void onUpdate();

		void onFinal();

	private:
		Sprite coinSprite;
		Font scoreText;
	};

	class GameScene final : public IScene {
	public:
		GameScene(SceneManager* _sceneManager);
		~GameScene();

		void onStart() override;

		void onUpdate() override;

		void onFinal() override;

		// プレイヤーを取得
		Player* getPlayer();

		// マップを取得
		Map* getMap();

		// 次のマップに移動
		void nextMap();

		// セレクトシーンへ戻る
		void changeSelectScene();

	private:
		SceneManager* sceneManager;    // SceneManagerへのポインタ
		vector<std::unique_ptr<IStage>> stages;
		GameSceneUI gameSceneUI;       // ゲームシーン内のUI
		Map* gameMap;                  // ゲームマップ
		Player player;                 // プレイヤー
		int currentStageNumber;          // 現在のマップの番号
	};
}

#endif // !GAMESCENE_H