#ifndef EFFECTMANAGER_H
#define EFFECTMANAGER_H

#include "Lib.h"
#include <vector>
#include <string>

namespace gnGame {
	class EffectManager {
	public:
		static EffectManager* getIns();

	public:
		~EffectManager() = default;

		void addEffect(int xNum, int yNum, const std::string& _imageName);

		void draw(int _index, const Vector2& _pos, const Vector2& _scale = { 1.0f, 1.0f });

	private:
		EffectManager() : effectList() {};
		EffectManager(const EffectManager&);
		EffectManager& operator= (const EffectManager&);

	private:
		std::vector<AnimSprite> effectList;
	};
}

#endif // !EFFECTMANAGER_H