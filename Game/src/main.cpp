#include "../include/Main.h"

void gnMain() {
	
	App app{ WindowInfo::WindowName, WindowInfo::WindowWidth, WindowInfo::WindowHeight };

	// マネージャの初期化
	TextureManager::addTexture("Back",        global::ImageAsset("BackGround.jpg"));
	TextureManager::addTexture("Player",      global::ImageAsset("Test_Player.png"));
	TextureManager::addTexture("Enemy",       global::ImageAsset("Enemy.png"));
	TextureManager::addTexture("Enemy1",      global::ImageAsset("Enemy1.png"));
	TextureManager::addTexture("Block",       global::ImageAsset("renga.png"));
	TextureManager::addTexture("Apple",       global::ImageAsset("Dot_Apple.png"));
	TextureManager::addTexture("floor",       global::ImageAsset("Floor.png"));
	TextureManager::addTexture("HPBar",       global::ImageAsset("HPLine.png"));
	TextureManager::addTexture("MPBar",       global::ImageAsset("MPLine.png"));
	TextureManager::addTexture("HPFrame",     global::ImageAsset("HPFrame.png"));
	TextureManager::addTexture("MPFrame",     global::ImageAsset("MPFrame.png"));
	TextureManager::addTexture("Test_Bullet", global::ImageAsset("Test_Bullet.png"));
	TextureManager::addTexture("Tako",        global::ImageAsset("Tako.png"));
	TextureManager::addTexture("Number",      global::ImageAsset("Numbers.png"));
	TextureManager::addTexture("UIFrame",     global::ImageAsset("UIFrame.png"));

	// ゲームシーンの初期化
	SceneManager s;
	s.initalize();

	while (app.update()) {
		app.begin();

		{
			s.update();
		}

		app.end();
	}

	s.finalize();
}