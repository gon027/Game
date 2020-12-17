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
		, bgTextures()
		, backGround()
		, size()
	{
		bgTextures.emplace_back(TextureManager::getTexture("bg1"));
		bgTextures.emplace_back(TextureManager::getTexture("bg2"));

		backGround.setTexture(bgTextures[0]);
	}

	void BackGround::setTexture(int _index)
	{
		backGround.setTexture(bgTextures[_index]);
	}

	void BackGround::draw()
	{
		backGround.draw(pos, Vector2::One, 0.0f, false);
	}
}
