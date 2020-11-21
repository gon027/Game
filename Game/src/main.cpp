#include "../include/Main.h"
#include "../include/TextureManager.h"

void gnMain() {
	
	App app{ WindowInfo::WindowName, WindowInfo::WindowWidth, WindowInfo::WindowHeight };

	// マネージャの初期化
	TextureManager::addTexture("Back",   "Asset/Image/BackGround.jpg");
	TextureManager::addTexture("Player", "Asset/Image/Test_Player.png");
	TextureManager::addTexture("Enemy",  "Asset/Image/Enemy.png");
	TextureManager::addTexture("Map",    "Asset/Image/MapData.png");
	TextureManager::addTexture("Block",  "Asset/Image/renga.png");
	TextureManager::addTexture("Apple",  "Asset/Image/Dot_Apple.png");

	// ゲームシーンの初期化
	Game gameScene;
	gameScene.onStart();

	while (app.doEvent()) {
		app.begin();

		{
			//Debug::drawFormatText(0, 0, Color::Black, "DeltaTime = %lf", Time::deltaTime());
			gameScene.onUpdate();
		}

		app.end();
	}

	gameScene.onFinal();
}