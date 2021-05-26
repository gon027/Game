#include "CoinScoreManager.h"

namespace gnGame {

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
