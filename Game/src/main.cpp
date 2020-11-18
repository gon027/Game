#include "../include/Main.h"
#include "../include/TextureManager.h"
#include "../include/EnemyManager.h"

#include <vector>
using namespace std;

void gnMain() {
	
	App app{ WindowInfo::WindowName, WindowInfo::WindowWidth, WindowInfo::WindowHeight };

	// マネージャの初期化
	TextureManager::addTexture("Back",   "Asset/Image/BackGround.jpg");
	TextureManager::addTexture("Player", "Asset/Image/Test_Player.png");
	TextureManager::addTexture("Enemy",  "Asset/Image/Enemy.png");
	TextureManager::addTexture("Map",    "Asset/Image/MapData.png");
	TextureManager::addTexture("Block",  "Asset/Image/renga.png");

	// ゲームシーンの初期化
	Game gameScene;
	gameScene.onStart();

	while (app.doEvent()) {
		app.begin();

		{
			gameScene.onUpdate(Time::deltaTime());
		}

		app.end();
	}

	gameScene.onFinal();
}