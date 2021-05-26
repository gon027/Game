#include "../include/Main.h"

// 画像を読み込みする
void loadTexture() {
	// 背景
	TextureManager::addTexture("Title_BG",      global::ImageAsset("bg/Title_BG.png"));
	TextureManager::addTexture("Select_BG",     global::ImageAsset("bg/Select_BG.png"));
	TextureManager::addTexture("Game_BG1",      global::ImageAsset("bg/Game_BG1.png"));
	TextureManager::addTexture("Game_BG2",      global::ImageAsset("bg/Game_BG2.png")); 

	// UI
	TextureManager::addTexture("Title",         global::ImageAsset("UI/Title.png"));
	TextureManager::addTexture("Number",        global::ImageAsset("UI/Numbers.png"));
	TextureManager::addTexture("HPBar",         global::ImageAsset("UI/HPLine.png"));
	TextureManager::addTexture("MPBar",         global::ImageAsset("UI/MPLine.png"));
	TextureManager::addTexture("HPFrame",       global::ImageAsset("UI/HPFrame.png"));
	TextureManager::addTexture("MPFrame",       global::ImageAsset("UI/MPFrame.png"));
	TextureManager::addTexture("UIFrame",       global::ImageAsset("UI/UIFrame.png"));

	// マップ内のオブジェクト
	TextureManager::addTexture("Goal",          global::ImageAsset("Object/Goal.png"));
	TextureManager::addTexture("Clear",         global::ImageAsset("Object/Clear.png"));
	TextureManager::addTexture("Move",          global::ImageAsset("Object/Move.png"));
	TextureManager::addTexture("Jump",          global::ImageAsset("Object/Jump.png"));
	TextureManager::addTexture("Shot",          global::ImageAsset("Object/Shot.png"));

	// マップデータ
	TextureManager::addTexture("MapChip",       global::ImageAsset("MapData/MapChip.png"));
	TextureManager::addTexture("Block",         global::ImageAsset("MapData/renga.png"));
	TextureManager::addTexture("floor",         global::ImageAsset("MapData/Floor.png"));

	// プレイヤー
	TextureManager::addTexture("Main_Walk",     global::ImageAsset("Player/Main_Walk.png"));
	TextureManager::addTexture("Main_Wait",     global::ImageAsset("Player/Main_Wait.png"));

	// 敵キャラ
	TextureManager::addTexture("Enemy1_Wait",     global::ImageAsset("Enemy/Enemy1_Wait.png"));
	TextureManager::addTexture("Enemy1_Action",   global::ImageAsset("Enemy/Enemy1_Action.png"));
	TextureManager::addTexture("Enemy2_Wait",     global::ImageAsset("Enemy/Enemy2_Wait.png"));
	TextureManager::addTexture("Enemy2_Action",   global::ImageAsset("Enemy/Enemy2_Action.png"));
	TextureManager::addTexture("Enemy3_Wait",     global::ImageAsset("Enemy/Enemy3_Wait.png"));
	TextureManager::addTexture("Enemy3_Action",   global::ImageAsset("Enemy/Enemy3_Action.png"));
	TextureManager::addTexture("Enemy4_Wait",     global::ImageAsset("Enemy/Enemy4_Wait.png"));
	TextureManager::addTexture("Enemy4_Action",   global::ImageAsset("Enemy/Enemy4_Action.png"));
	TextureManager::addTexture("BigEnemy_Wait",   global::ImageAsset("Enemy/BigEnemy_Wait.png"));
	TextureManager::addTexture("BigEnemy_Action", global::ImageAsset("Enemy/BigEnemy_Action.png"));
	TextureManager::addTexture("Boss_Wait",       global::ImageAsset("Enemy/Boss_Wait.png"));
	TextureManager::addTexture("Boss_Action",     global::ImageAsset("Enemy/Boss_Action.png"));
	TextureManager::addTexture("Tutorial_Boss",   global::ImageAsset("Enemy/Tutorial_Boss.png"));

	// トラップ
	TextureManager::addTexture("Needle",        global::ImageAsset("Trap/DoubleNeedle.png"));

	// アイテム
	TextureManager::addTexture("Apple",         global::ImageAsset("Item/Apple.png"));
	TextureManager::addTexture("Coin",          global::ImageAsset("Item/Coin.png"));

	// バレット
	TextureManager::addTexture("Red_Bullet",    global::ImageAsset("Bullet/Red_Bullet.png"));
	TextureManager::addTexture("Yellow_Bullet", global::ImageAsset("Bullet/Yellow_Bullet.png"));

	// エフェクト
	// TextureManager::addTexture("Effect", global::ImageAsset("Effect/effect.png"));
}

/*
// エフェクトを読み込む
void loadEffect() {
	EffectManager::getIns()->addEffect(5, 1, "Effect");
}
*/

void gnMain() {
	App::init(WindowInfo::WindowName, WindowInfo::WindowWidth, WindowInfo::WindowHeight);

	loadTexture();

	//loadEffect();

	// ゲームシーンの初期化
	SceneManager scene;
	scene.initalize();

	while (App::update()) {
		App::begin();

		scene.update();

		App::end();
	}

	scene.finalize();
}