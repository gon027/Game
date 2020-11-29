#include "../include/Main.h"
#include "../include/TextureManager.h"


#include "../include/SceneManager.h"
#include "../include/TitleScene.h"
#include "../include/SelectScene.h"

void gnMain() {
	
	App app{ WindowInfo::WindowName, WindowInfo::WindowWidth, WindowInfo::WindowHeight };

	// マネージャの初期化
	TextureManager::addTexture("Back",   "Asset/Image/BackGround.jpg");
	TextureManager::addTexture("Player", "Asset/Image/Test_Player.png");
	TextureManager::addTexture("Enemy", "Asset/Image/Enemy.png");
	TextureManager::addTexture("Enemy1",  "Asset/Image/Enemy1.png");
	TextureManager::addTexture("Map",    "Asset/Image/MapData.png");
	TextureManager::addTexture("Block",  "Asset/Image/renga.png");
	TextureManager::addTexture("Apple",  "Asset/Image/Dot_Apple.png");
	TextureManager::addTexture("floor", "Asset/Image/Floor.png");
	TextureManager::addTexture("BarFrame", "Asset/Image/BarFrame.png");
	TextureManager::addTexture("HPBar",  "Asset/Image/HPLine.png");
	TextureManager::addTexture("MPBar", "Asset/Image/MPLine.png");
	TextureManager::addTexture("HPFrame", "Asset/Image/HPFrame.png");
	TextureManager::addTexture("MPFrame", "Asset/Image/MPFrame.png");

	// ゲームシーンの初期化
	Game gameScene;
	gameScene.onStart();

	//SceneManager s;
	//s.initalize();

	while (app.doEvent()) {
		app.begin();

		{
			//Debug::drawFormatText(0, 0, Color::Black, "DeltaTime = %lf", Time::deltaTime());
			gameScene.onUpdate();
			//s.update();
		}

		app.end();
	}

	//s.finalize();
	gameScene.onFinal();
	
}