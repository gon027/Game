#ifndef STAGENUMBER_H
#define STAGENUMBER_H

namespace gnGame {

	// �X�e�[�W�̔ԍ��Ɖ������Ă���X�e�[�W���Ǘ�����N���X
	class StageManager {
	public:
		// �X�e�[�W�̍ő吔
		static const int MAXSTAGE{ 4 };

	public:
		static StageManager* getIns();

	public:
		// �X�e�[�W���A�����b�N������
		void unlockStage();

		// �A�����b�N����U��X�e�[�W���擾
		int getUnlockCurrentStage();

		// �X�e�[�W�ԍ���1�i�߂�
		void incrementCurrentStage();

		// �X�e�[�W�ԍ���1�߂�
		void decrementCurrentStage();

		// ���݂̃X�e�[�W�ԍ����擾����
		int getCurrentStage();

	private:
		StageManager() {};
		StageManager(const StageManager&);
		StageManager& operator= (const StageManager&);

	private:
		// ���� : �`���[�g���A�����܂߂Q
		int UnlockCurrentStage{ 1 };

		// ���݂̃X�e�[�W
		int currentStage{ 0 };
	};

}

#endif // !STAGENUMBER_H