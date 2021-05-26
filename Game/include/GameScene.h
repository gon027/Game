#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <vector>
#include <string>
#include "Lib.h"
#include "Scene.h"
#include "Player.h"
#include "BackGround.h"

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

		// マップをリセットする
		void resetMap();

		// 最初に呼ばれるマップの初期化
		void initMap();

		// 次のマップに移動
		void nextMap();

		// セレクトシーンへ戻る
		void changeSelectScene();

	private:
		SceneManager* sceneManager;    // SceneManagerへのポインタ
		GameSceneUI gameSceneUI;       // ゲームシーン内のUI
		BackGround backGround;         // 背景
		Map* gameMap;                  // ゲームマップ
		Player player;                 // プレイヤー
		int currentMapNumber;          // 現在のマップの番号
		AudioSource stageBgm;          // ゲームシーン上のBGM
	};
}

#endif // !GAMESCENE_H