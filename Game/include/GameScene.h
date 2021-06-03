#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <vector>
#include <string>
#include "Lib.h"
#include "Scene.h"
#include "Player.h"
#include "BackGround.h"
#include "Stage.h"

namespace gnGame {

	class SceneManager;
	class Map;

	class GameSceneUI {
	public:
		GameSceneUI();
		~GameSceneUI() = default;

		void onStart();

		void onUpdate();

		void onFinal();

	private:
		Sprite coinSprite;
		Font scoreText;
	};

	class GameScene final : public IScene {
	public:
		GameScene(SceneManager* _sceneManager);
		~GameScene();

		void onStart() override;

		void onUpdate() override;

		void onFinal() override;

		// �v���C���[���擾
		Player* getPlayer();

		// �}�b�v���擾
		Map* getMap();

		// ���̃}�b�v�Ɉړ�
		void nextMap();

		// �Z���N�g�V�[���֖߂�
		void changeSelectScene();

	private:
		SceneManager* sceneManager;    // SceneManager�ւ̃|�C���^
		vector<std::unique_ptr<IStage>> stages;
		GameSceneUI gameSceneUI;       // �Q�[���V�[������UI
		Map* gameMap;                  // �Q�[���}�b�v
		Player player;                 // �v���C���[
		int currentStageNumber;          // ���݂̃}�b�v�̔ԍ�
	};
}

#endif // !GAMESCENE_H