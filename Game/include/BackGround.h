#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector>
#include "TextureManager.h"

namespace gnGame {

	class BackGround {
	public:
		BackGround();
		~BackGround() = default;

		// �e�N�X�`����ύX����
		void setTexture(int _index);

		// �`�悷��
		void draw();

	private:
		Vector2 pos;
		Size size;
		std::vector<TexturePtr> bgTextures;
		Sprite backGround;
	};
}

#endif // !BACKGROUND_H
