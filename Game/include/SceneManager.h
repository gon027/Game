#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <memory>
#include <vector>
#include "Scene.h"

namespace gnGame {

	enum class SceneType {
		Title,     // タイトルシーン
		Select,    // セレクトシーン
		Game,      // ゲームシーン
	};

	class SceneManager {
	public:
		using ScenePtr = std::shared_ptr<IScene>;
		using SceneList = std::vector<ScenePtr>;
		using CurrentScene = std::weak_ptr<IScene>;

	public:
		SceneManager();
		~SceneManager() = default;

		// 初期化
		void initalize();

		// 更新
		void update();

		// 最後の処理
		void finalize();

		// シーンを切り替える
		void changeScene(SceneType _sceneType);

	private:
		SceneList sceneList;        // シーンを保存するリスト
		CurrentScene currentScene;  // 実行しているシーン
		SceneType sceneType;        // 現在のシーンの状態
	};
}


#endif // !SCENEMANAGER_H
