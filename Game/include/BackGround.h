#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector>
#include "TextureManager.h"

namespace gnGame {

	class BackGround {
	public:
		BackGround();
		~BackGround() = default;

		// テクスチャを変更する
		void setTexture(int _index);

		// 描画する
		void draw();

	private:
		Vector2 pos;
		Size size;
		std::vector<TexturePtr> bgTextures;
		Sprite backGround;
	};
}

#endif // !BACKGROUND_H
