#include "../include/GameScene.h"
#include "../include/SceneManager.h"
#include "../include/StageManager.h"

namespace gnGame {

	GameScene::GameScene(SceneManager* _sceneManager)
		: sceneManager(_sceneManager)
		, gameMap(nullptr)
		, player()
		, currentMapNumber(0)
	{
	}

	GameScene::~GameScene()
	{
		if (gameMap) {
			delete gameMap;
			gameMap = nullptr;
		}
	}

	void GameScene::onStart()
	{
	}

	void GameScene::onUpdate()
	{
		Debug::drawText(0, 0, "GameScene");
		//Debug::drawFormatText(0, 40, Color::Red, "%d", &StageManager::currentStage);

		if (Input::getKeyDown(Key::Z)) {
			sceneManager->changeScene(SceneType::Title);
		}
	}

	void GameScene::onFinal()
	{
	}

	Player* GameScene::getPlayer()
	{
		return &player;
	}

	Map* GameScene::getMap()
	{
		return gameMap;
	}

	void GameScene::resetMap()
	{
	}

	void GameScene::nextMap()
	{
	}

}
