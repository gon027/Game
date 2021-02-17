#include "../include/Main.h"

// �摜��ǂݍ��݂���
void loadTexture() {
	// �e�X�g�p
	TextureManager::addTexture("Enemy1",        global::ImageAsset("Enemy1.png"));
	TextureManager::addTexture("Tako",          global::ImageAsset("Tako.png"));
	TextureManager::addTexture("Boss",          global::ImageAsset("Boss.png"));
	TextureManager::addTexture("Effect",        global::ImageAsset("effect.png"));

	// �w�i
	TextureManager::addTexture("Title_BG",      global::ImageAsset("bg/Title_BG.png"));
	TextureManager::addTexture("Select_BG",     global::ImageAsset("bg/Select_BG.png"));
	TextureManager::addTexture("Game_BG1",      global::ImageAsset("bg/Game_BG1.png"));
	TextureManager::addTexture("Game_BG2",      global::ImageAsset("bg/Game_BG2.png")); 

	// UI
	TextureManager::addTexture("Number",        global::ImageAsset("UI/Numbers.png"));
	TextureManager::addTexture("HPBar",         global::ImageAsset("UI/HPLine.png"));
	TextureManager::addTexture("MPBar",         global::ImageAsset("UI/MPLine.png"));
	TextureManager::addTexture("HPFrame",       global::ImageAsset("UI/HPFrame.png"));
	TextureManager::addTexture("MPFrame",       global::ImageAsset("UI/MPFrame.png"));
	TextureManager::addTexture("UIFrame",       global::ImageAsset("UI/UIFrame.png"));

	// �}�b�v���̃I�u�W�F�N�g
	TextureManager::addTexture("Goal",          global::ImageAsset("Object/Goal.png"));
	TextureManager::addTexture("Move",          global::ImageAsset("Object/Move.png"));
	TextureManager::addTexture("Jump",          global::ImageAsset("Object/Jump.png"));
	TextureManager::addTexture("Shot",          global::ImageAsset("Object/Shot.png"));

	// �}�b�v�f�[�^
	TextureManager::addTexture("MapChip",       global::ImageAsset("MapData/MapChip.png"));
	TextureManager::addTexture("Block",         global::ImageAsset("MapData/renga.png"));
	TextureManager::addTexture("floor",         global::ImageAsset("MapData/Floor.png"));

	// �v���C���[
	TextureManager::addTexture("Main_Walk",     global::ImageAsset("Player/Main_Walk.png"));
	TextureManager::addTexture("Main_Wait",     global::ImageAsset("Player/Main_Wait.png"));

	// �G�L����
	TextureManager::addTexture("Enemy1_Wait",   global::ImageAsset("Enemy/Enemy1_Wait.png"));
	TextureManager::addTexture("Enemy1_Action", global::ImageAsset("Enemy/Enemy1_Action.png"));
	TextureManager::addTexture("Enemy2_Wait",   global::ImageAsset("Enemy/Enemy2_Wait.png"));
	TextureManager::addTexture("Enemy2_Action", global::ImageAsset("Enemy/Enemy2_Action.png"));
	TextureManager::addTexture("Enemy3_Wait",   global::ImageAsset("Enemy/Enemy3_Wait.png"));
	TextureManager::addTexture("Enemy3_Action", global::ImageAsset("Enemy/Enemy3_Action.png"));
	TextureManager::addTexture("Enemy4_Wait",   global::ImageAsset("Enemy/Enemy4_Wait.png"));
	TextureManager::addTexture("Enemy4_Action", global::ImageAsset("Enemy/Enemy4_Action.png"));
	TextureManager::addTexture("Tutorial_Boss", global::ImageAsset("Enemy/Tutorial_Boss.png"));

	// �g���b�v
	TextureManager::addTexture("Needle",        global::ImageAsset("Trap/DoubleNeedle.png"));

	// �A�C�e��
	TextureManager::addTexture("Apple",         global::ImageAsset("Item/Apple.png"));

	// �o���b�g
	TextureManager::addTexture("Red_Bullet",    global::ImageAsset("Bullet/Red_Bullet.png"));
	TextureManager::addTexture("Yellow_Bullet", global::ImageAsset("Bullet/Yellow_Bullet.png"));
}

// �G�t�F�N�g��ǂݍ���
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

	// �Q�[���V�[���̏�����
	SceneManager scene;
	scene.initalize();

	while (app.update()) {
		app.begin();
		scene.update();
		app.end();
	}

	scene.finalize();
}