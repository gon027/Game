#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "Lib.h"
#include "Scene.h"
#include "Camera.h"
#include "Map.h"
#include "Player.h"
#include "Fps.h"
#include "BackGround.h"

namespace gnGame {

	using MapList = std::vector<std::string>;

	class Game : public IScene{
	public:
		Game();
		~Game();

		void onStart() override;
		void onUpdate() override;
		void onFinal() override;

		// �v���C���[���擾
		Player* getPlayer();

		// �}�b�v���擾
		Map* getMap();

		// �}�b�v�����Z�b�g����
		void resetMap();

		// ���̃X�e�[�W�ɑ@��
		void nextStage();

	private:
		Fps fps;
		Map* map;
		Player player;
		BackGround bg;
		MapList mapList;
		int currentMap{ 0 };
	};
}

#endif // !GAME_H
