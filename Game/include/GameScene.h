#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <vector>
#include <string>
#include "Lib.h"
#include "Scene.h"
#include "Player.h"
#include "BackGround.h"

namespace gnGame {

	class SceneManager;
	class Map;

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

		// �}�b�v�����Z�b�g����
		void resetMap();

		// �ŏ��ɌĂ΂��}�b�v�̏�����
		void initMap();

		// ���̃}�b�v�Ɉړ�
		void nextMap();

	private:
		SceneManager* sceneManager;    // SceneManager�ւ̃|�C���^
		Map* gameMap;                  // �Q�[���}�b�v
		Player player;                 // �v���C���[
		int currentMapNumber;          // ���݂̃}�b�v�̔ԍ�
	};
}

#endif // !GAMESCENE_H