#ifndef COINSCOREMANAGER_H
#define COINSCOREMANAGER_H

namespace gnGame {
	
	class CoinScoreManager {
	private:

		// �R�C���̃X�R�A�̍\����
		struct CoinScore {
			int score{ 0 };
		};

	public:
		// �X�R�A�����Z
		void addScore();

		// �X�R�A�����Z�b�g
		void resetScore();

		// �X�R�A�̒l���擾
		int getScore() const;

	private:
		CoinScoreManager() : coinScore({}) {};
		CoinScoreManager(const CoinScoreManager&);
		CoinScoreManager& operator= (const CoinScoreManager&);

	private:
		CoinScore coinScore;
	};

}

#endif // !COINSCOREMANAGER_H
