#include "CoinScoreManager.h"

namespace gnGame {

	CoinScoreManager* CoinScoreManager::getIns()
	{
		static CoinScoreManager Instance;
		return &Instance;
	}

	void gnGame::CoinScoreManager::addScore()
	{
		++coinScore.score;
	}

	void gnGame::CoinScoreManager::resetScore()
	{
		coinScore.score = 0;
	}

	int gnGame::CoinScoreManager::getScore() const
	{
		return coinScore.score;
	}

}
