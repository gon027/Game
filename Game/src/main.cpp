#include "../include/Main.h"

#include "../include/TestMain.h"

// �摜��ǂݍ��݂���
void loadTexture() {
	// �w�i
	TextureManager::addTexture("Title_BG",      "bg/Title_BG.png");
	TextureManager::addTexture("Select_BG",     "bg/Select_BG.png");
	TextureManager::addTexture("Game_BG1",      "bg/Game_BG1.png");
	TextureManager::addTexture("Game_BG2",      "bg/Game_BG2.png"); 

	// UI
	TextureManager::addTexture("Title",         "UI/Title.png");
	TextureManager::addTexture("Number",        "UI/Numbers.png");
	TextureManager::addTexture("HPBar",         "UI/HPLine.png");
	TextureManager::addTexture("MPBar",         "UI/MPLine.png");
	TextureManager::addTexture("HPFrame",       "UI/HPFrame.png");
	TextureManager::addTexture("MPFrame",       "UI/MPFrame.png");
	TextureManager::addTexture("UIFrame",       "UI/UIFrame.png");

	// �}�b�v���̃I�u�W�F�N�g
	TextureManager::addTexture("Goal",          "Object/Goal.png");
	TextureManager::addTexture("Clear",         "Object/Clear.png");
	TextureManager::addTexture("Move",          "Object/Move.png");
	TextureManager::addTexture("Jump",          "Object/Jump.png");
	TextureManager::addTexture("Shot",          "Object/Shot.png");

	// �}�b�v�f�[�^
	TextureManager::addTexture("MapChip",       "MapData/MapChip.png");
	TextureManager::addTexture("Block",         "MapData/renga.png");
	TextureManager::addTexture("floor",         "MapData/Floor.png");

	// �v���C���[
	TextureManager::addTexture("Main_Walk",     "Player/Main_Walk.png");
	TextureManager::addTexture("Main_Wait",     "Player/Main_Wait.png");

	// �G�L����
	TextureManager::addTexture("Enemy1_Wait",     "Enemy/Enemy1_Wait.png");
	TextureManager::addTexture("Enemy1_Action",   "Enemy/Enemy1_Action.png");
	TextureManager::addTexture("Enemy2_Wait",     "Enemy/Enemy2_Wait.png");
	TextureManager::addTexture("Enemy2_Action",   "Enemy/Enemy2_Action.png");
	TextureManager::addTexture("Enemy3_Wait",     "Enemy/Enemy3_Wait.png");
	TextureManager::addTexture("Enemy3_Action",   "Enemy/Enemy3_Action.png");
	TextureManager::addTexture("Enemy4_Wait",     "Enemy/Enemy4_Wait.png");
	TextureManager::addTexture("Enemy4_Action",   "Enemy/Enemy4_Action.png");
	TextureManager::addTexture("BigEnemy_Wait",   "Enemy/BigEnemy_Wait.png");
	TextureManager::addTexture("BigEnemy_Action", "Enemy/BigEnemy_Action.png");
	TextureManager::addTexture("Boss_Wait",       "Enemy/Boss_Wait.png");
	TextureManager::addTexture("Boss_Action",     "Enemy/Boss_Action.png");
	TextureManager::addTexture("Tutorial_Boss",   "Enemy/Tutorial_Boss.png");

	// �g���b�v
	TextureManager::addTexture("Needle",        "Trap/DoubleNeedle.png");

	// �A�C�e��
	TextureManager::addTexture("Apple",         "Item/Apple.png");
	TextureManager::addTexture("Coin",          "Item/Coin.png");

	// �o���b�g
	TextureManager::addTexture("Red_Bullet",    "Bullet/Red_Bullet.png");
	TextureManager::addTexture("Yellow_Bullet", "Bullet/Yellow_Bullet.png");
}

// ���y�t�@�C����ǂݍ���
void loadAudio() {
	AudioManager::getIns()->loadAudio("BGM_game", "bgm.wav");
	AudioManager::getIns()->loadAudio("SE_coin",   "se_coin.wav");
	AudioManager::getIns()->loadAudio("SE_jump",   "se_jump.wav");
	AudioManager::getIns()->loadAudio("SE_select", "se_select.wav");
	AudioManager::getIns()->loadAudio("SE_shot",   "se_shot.wav");
}

void gnMain() {
	App::init(WindowInfo::WindowName, WindowInfo::WindowWidth, WindowInfo::WindowHeight);

	
	loadTexture();
	loadAudio();

	// �Q�[���V�[���̏�����
	SceneManager scene;
	scene.initalize();
	

	//test::TestMain t;

	while (App::update()) {
		App::begin();

		scene.update();
		//t.run();

		App::end();
	}

	scene.finalize();
}