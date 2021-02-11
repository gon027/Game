#include "../include/Main.h"

// 画像を読み込みする
void loadTexture() {
	// テスト用
	TextureManager::addTexture("Enemy1",        global::ImageAsset("Enemy1.png"));
	TextureManager::addTexture("Test_Bullet",   global::ImageAsset("Test_Bullet.png"));
	TextureManager::addTexture("Tako",          global::ImageAsset("Tako.png"));
	TextureManager::addTexture("bg1",           global::ImageAsset("abg1.png"));
	TextureManager::addTexture("bg2",           global::ImageAsset("abg2.png"));
	TextureManager::addTexture("bg3",           global::ImageAsset("abg3.png"));
	TextureManager::addTexture("Boss",          global::ImageAsset("Boss.png"));
	TextureManager::addTexture("Effect",        global::ImageAsset("effect.png"));

	// UI
	TextureManager::addTexture("Number",        global::ImageAsset("UI/Numbers.png"));
	TextureManager::addTexture("HPBar",         global::ImageAsset("UI/HPLine.png"));
	TextureManager::addTexture("MPBar",         global::ImageAsset("UI/MPLine.png"));
	TextureManager::addTexture("HPFrame",       global::ImageAsset("UI/HPFrame.png"));
	TextureManager::addTexture("MPFrame",       global::ImageAsset("UI/MPFrame.png"));
	TextureManager::addTexture("UIFrame",       global::ImageAsset("UI/UIFrame.png"));

	// マップデータ
	TextureManager::addTexture("MapChip",       global::ImageAsset("MapData/MapChip.png"));
	TextureManager::addTexture("Block",         global::ImageAsset("MapData/renga.png"));
	TextureManager::addTexture("floor",         global::ImageAsset("MapData/Floor.png"));

	// プレイヤー
	TextureManager::addTexture("Main_Walk",     global::ImageAsset("Player/Main_Walk.png"));
	TextureManager::addTexture("Main_Wait",     global::ImageAsset("Player/Main_Wait.png"));

	// 敵キャラ
	TextureManager::addTexture("Enemy1_Wait",   global::ImageAsset("Enemy/Enemy1_Wait.png"));
	TextureManager::addTexture("Enemy1_Action", global::ImageAsset("Enemy/Enemy1_Action.png"));
	TextureManager::addTexture("Enemy2_Wait",   global::ImageAsset("Enemy/Enemy2_Wait.png"));
	TextureManager::addTexture("Enemy2_Action", global::ImageAsset("Enemy/Enemy2_Action.png"));
	TextureManager::addTexture("Enemy3_Wait",   global::ImageAsset("Enemy/Enemy3_Wait.png"));
	TextureManager::addTexture("Enemy3_Action", global::ImageAsset("Enemy/Enemy3_Action.png"));
	TextureManager::addTexture("Enemy4_Wait",   global::ImageAsset("Enemy/Enemy4_Wait.png"));
	TextureManager::addTexture("Enemy4_Action", global::ImageAsset("Enemy/Enemy4_Action.png"));

	// アイテム
	TextureManager::addTexture("Apple",       global::ImageAsset("Item/Apple.png"));
}

// エフェクトを読み込む
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

	// ゲームシーンの初期化
	SceneManager scene;
	scene.initalize();

	while (app.update()) {
		app.begin();
		scene.update();
		app.end();
	}

	scene.finalize();
}