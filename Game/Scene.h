#ifndef SCENE_H
#define SCENE_H

class IScene {
public:
	virtual ~IScene() = default;

	// 最初に実行される関数
	virtual void onStart() = 0;

	// 更新関数
	virtual void onUpdate() = 0;
};

#endif // !SCENE_H
