#ifndef SCENE_H
#define SCENE_H

namespace gnGame {

	// シーンの基底クラス
	class IScene {
	public:
		virtual ~IScene() = default;

		// 最初に実行される関数
		virtual void onStart() = 0;

		// 更新関数
		virtual void onUpdate() = 0;

		// 最後に実行される関数
		virtual void onFinal() = 0;
	};
}

#endif // !SCENE_H
