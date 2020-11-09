#ifndef SCENE_H
#define SCENE_H

class IScene {
public:
	virtual ~IScene() = default;

	// Å‰‚ÉÀs‚³‚ê‚éŠÖ”
	virtual void onStart() = 0;

	// XVŠÖ”
	virtual void onUpdate() = 0;
};

#endif // !SCENE_H
