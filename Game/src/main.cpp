#include "../include/Main.h"
#include "../include/TextureManager.h"


#include "../include/SceneManager.h"
#include "../include/TitleScene.h"
#include "../include/SelectScene.h"

void gnMain() {
	
	App app{ WindowInfo::WindowName, WindowInfo::WindowWidth, WindowInfo::WindowHeight };

	// マネージャの初期化
	// TextureManager::addTexture("Back",   "Asset/Image/BackGround.jpg");
	// TextureManager::addTexture("Player", "Asset/Image/Test_Player.png");
	// TextureManager::addTexture("Enemy",  "Asset/Image/Enemy.png");
	// TextureManager::addTexture("Map",    "Asset/Image/MapData.png");
	// TextureManager::addTexture("Block",  "Asset/Image/renga.png");
	// TextureManager::addTexture("Apple",  "Asset/Image/Dot_Apple.png");
	// TextureManager::addTexture("floor",  "Asset/Image/floor.png");

	// ゲームシーンの初期化
	//Game gameScene;
	//gameScene.onStart();

	SceneManager s;
	s.initalize();

	while (app.doEvent()) {
		app.begin();

		{
			//Debug::drawFormatText(0, 0, Color::Black, "DeltaTime = %lf", Time::deltaTime());
			//gameScene.onUpdate();
			s.update();
		}

		app.end();
	}

	s.finalize();
	//gameScene.onFinal();
	
}