#ifndef COINSCOREMANAGER_H
#define COINSCOREMANAGER_H

namespace gnGame {
	
	class CoinScoreManager {
	private:

		// コインのスコアの構造体
		struct CoinScore {
			int score{ 0 };
		};

	public:
		// スコアを加算
		void addScore();

		// スコアをリセット
		void resetScore();

		// スコアの値を取得
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
