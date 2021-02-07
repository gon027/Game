#include "../include/Main.h"

void loadTexture() {
	// ‰æ‘œ‚ğ“Ç‚İ‚İ‚·‚é
	TextureManager::addTexture("HPBar",       global::ImageAsset("HPLine.png"));
	TextureManager::addTexture("MPBar",       global::ImageAsset("MPLine.png"));
	TextureManager::addTexture("HPFrame",     global::ImageAsset("HPFrame.png"));
	TextureManager::addTexture("MPFrame",     global::ImageAsset("MPFrame.png"));
	TextureManager::addTexture("UIFrame",     global::ImageAsset("UIFrame.png"));
	TextureManager::addTexture("Player",      global::ImageAsset("Test_Player.png"));
	TextureManager::addTexture("Enemy",       global::ImageAsset("Enemy.png"));
	TextureManager::addTexture("Enemy1",      global::ImageAsset("Enemy1.png"));
	TextureManager::addTexture("Block",       global::ImageAsset("renga.png"));
	TextureManager::addTexture("Apple",       global::ImageAsset("Dot_Apple.png"));
	TextureManager::addTexture("floor",       global::ImageAsset("Floor.png"));
	TextureManager::addTexture("Test_Bullet", global::ImageAsset("Test_Bullet.png"));
	TextureManager::addTexture("Tako",        global::ImageAsset("Tako.png"));
	TextureManager::addTexture("Number",      global::ImageAsset("Numbers.png"));
	TextureManager::addTexture("bg1",         global::ImageAsset("abg1.png"));
	TextureManager::addTexture("bg2",         global::ImageAsset("abg2.png"));
	TextureManager::addTexture("bg3",         global::ImageAsset("abg3.png"));
	TextureManager::addTexture("MapChip",     global::ImageAsset("MapChip.png"));
	TextureManager::addTexture("Boss",        global::ImageAsset("Boss.png"));
	TextureManager::addTexture("Effect",      global::ImageAsset("effect.png"));
	TextureManager::addTexture("Enemy1_Wait", global::ImageAsset("Enemy1_Wait.png"));
	TextureManager::addTexture("Enemy1_Action", global::ImageAsset("Enemy1_Action.png"));
	TextureManager::addTexture("Enemy2_Action", global::ImageAsset("Enemy2_Action.png"));
}

void loadEffect() {
	EffectManager::getIns()->addEffect(5, 1, "Effect");
}

void gnMain() {
	App app{
		WindowInfo::WindowName, 
		WindowInfo::WindowWidth,
		WindowInfo::WindowHeight
	};

	loadTexture();

	loadEffect();

	// ƒQ[ƒ€ƒV[ƒ“‚Ì‰Šú‰»
	SceneManager scene;
	scene.initalize();

	while (app.update()) {
		app.begin();
		scene.update();
		app.end();
	}

	scene.finalize();
}