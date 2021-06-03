#ifndef STAGE_H
#define STAGE_H

#include <vector>
#include <string>
#include "BackGround.h"
#include "Map.h"

namespace gnGame {

	using std::vector;
	using std::string;

	class Player;

	class IStage {
	public:
		virtual ~IStage() = default;

		virtual void onStart() = 0;

		virtual void onUpdate() = 0;

		virtual void onFinal() = 0;

		// �ŏ��ɌĂ΂��}�b�v�̏�����
		virtual void initMap() = 0;

		// ���̃}�b�v�Ɉړ�
		virtual void nextMap() = 0;

		// �}�b�v�����Z�b�g����
		virtual void resetMap() = 0;
	};

	/// <summary>
	/// �`���[�g���A���X�e�[�W
	/// </summary>
	class TutorialStage final : public IStage {
	public:
		TutorialStage(Map* _map, Player* _player);
		~TutorialStage() = default;

		void onStart() override;
						
		void onUpdate() override;
						
		void onFinal() override;
						
		void initMap() override;
						
		void nextMap() override;
						
		void resetMap() override;

	private:
		vector<string> mapNameList;
		BackGround backGround;         // �w�i
		Map* gameMap;                  // �Q�[���}�b�v
		Player* player;                // �v���C���[�̃|�C���^
		int currentMapNumber;          // ���݂̃}�b�v�̔ԍ�
	};
	
	/// <summary>
	/// �X�e�[�W�P
	/// </summary>
	class Stage1 final : public IStage {
	public:
		Stage1(Map* _map, Player* _player);
		~Stage1() = default;

		void onStart() override;

		void onUpdate() override;

		void onFinal() override;

		void initMap() override;

		void nextMap() override;

		void resetMap() override;

	private:
		vector<string> mapNameList;
		BackGround backGround;         // �w�i
		Map* gameMap;                  // �Q�[���}�b�v
		Player* player;                // �v���C���[�̃|�C���^
		int currentMapNumber;          // ���݂̃}�b�v�̔ԍ�
	};

	/// <summary>
	/// �X�e�[�W�Q
	/// </summary>
	class Stage2 final : public IStage {
	public:
		Stage2(Map* _map, Player* _player);
		~Stage2() = default;

		void onStart() override;

		void onUpdate() override;

		void onFinal() override;

		void initMap() override;

		void nextMap() override;

		void resetMap() override;
	private:
		vector<string> mapNameList;
		BackGround backGround;         // �w�i
		Map* gameMap;                  // �Q�[���}�b�v
		Player* player;                // �v���C���[�̃|�C���^
		int currentMapNumber;          // ���݂̃}�b�v�̔ԍ�
	};

	/// <summary>
	/// �{�X�X�e�[�W
	/// </summary>
	class BossStage final : public IStage {
	public:
		BossStage(Map* _map, Player* _player);
		~BossStage() = default;

		void onStart() override;

		void onUpdate() override;

		void onFinal() override;

		void initMap() override;

		void nextMap() override;

		void resetMap() override;

	private:
		vector<string> mapNameList;
		BackGround backGround;         // �w�i
		Map* gameMap;                  // �Q�[���}�b�v
		Player* player;                // �v���C���[�̃|�C���^
		int currentMapNumber;          // ���݂̃}�b�v�̔ԍ�
	};

	class DebugStage final : public IStage {
	public:
		DebugStage(Map* _map, Player* _player);
		~DebugStage() = default;

		void onStart() override;

		void onUpdate() override;

		void onFinal() override;

		void initMap() override;

		void nextMap() override;

		void resetMap() override;

	private:
		vector<string> mapNameList;
		BackGround backGround;         // �w�i
		Map* gameMap;                  // �Q�[���}�b�v
		Player* player;                // �v���C���[�̃|�C���^
		int currentMapNumber;          // ���݂̃}�b�v�̔ԍ�
	};


}

#endif // STAGE_H