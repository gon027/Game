#include "../include/BackGround.h"
#include "../include/WindowInfo.h"
#include "../include/Camera.h"
#include "../include/TextureManager.h"

namespace gnGame {

	namespace Static {
		constexpr int wWidth = WindowInfo::WindowWidth;
		constexpr int wHeight = WindowInfo::WindowHeight;
	}

	BackGround::BackGround()
		: pos()
		, bgNameList()
		, backGround()
	{
		bgNameList.emplace_back("Game_BG1");
		bgNameList.emplace_back("Game_BG2");

		backGround.setTexture(TextureManager::getTexture(bgNameList[0]));
	}

	void BackGround::setTexture(int _index)
	{
		backGround.setTexture(TextureManager::getTexture(bgNameList[_index]));
	}

	void BackGround::draw()
	{
		backGround.draw(pos, Vector2::One, 0.0f, false);
	}
}
