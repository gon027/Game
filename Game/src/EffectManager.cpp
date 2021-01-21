#include "../include/EffectManager.h"
#include "../include/TextureManager.h"

namespace gnGame {

	EffectManager* EffectManager::getIns()
	{
		static EffectManager Instance;
		return &Instance;
	}

	void EffectManager::addEffect(int _xNum, int _yNum, const std::string& _imageName)
	{
		AnimSprite anim(_xNum, _yNum, 24.0f);
		anim.setTexture(TextureManager::getTexture(_imageName));
		effectList.emplace_back(anim);
	}

	void EffectManager::draw(int _index, const Vector2& _pos, const Vector2& _scale)
	{
		effectList[_index].draw(_pos, _scale, 0.0f);
	}

}