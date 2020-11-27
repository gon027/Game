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

	Sprite s, ss, fe, mf;
	s.setTexture(TextureManager::getTexture("HPBar"));
	ss.setTexture(TextureManager::getTexture("MPBar"));
	fe.setTexture(TextureManager::getTexture("HPFrame"));
	mf.setTexture(TextureManager::getTexture("MPFrame"));


	float f = 0.0f;

	while (app.doEvent()) {
		app.begin();

		{
			//Debug::drawFormatText(0, 0, Color::Black, "DeltaTime = %lf", Time::deltaTime());
			gameScene.onUpdate();
			//s.update();

			f += Time::deltaTime();
			//fe.draw({ 0, 0 }, { 1, 1.0f }, 0.0f, false);
			//mf.draw({ 0, 32 }, { 1, 1.0f }, 0.0f, false);
			//s.draw({ 16 * 6.8125f - 16 * f / 20.f, 0 }, { 7.8125f - f / 20.f, 1.0f }, 0.0f, false);
			//ss.draw({ 16 * 6.8125f - 16 * f * 0.1f, 32 }, { 7.8125f - f * 0.1f, 1.0f }, 0.0f, false);
			
		}

		app.end();
	}

	//s.finalize();
	gameScene.onFinal();
	
}