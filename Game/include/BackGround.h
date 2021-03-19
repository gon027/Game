#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector>
#include <string>
#include "Lib.h"

namespace gnGame {

	/// <summary>
	/// �w�i�N���X
	/// </summary>
	class BackGround {
	public:
		BackGround();
		~BackGround() = default;

		/// <summary>
		/// �w�i�̉摜���Z�b�g����
		/// </summary>
		/// <param name="_index"> bgNameList�̓Y�����ԍ� </param>
		void setTexture(int _index);

		// �`�悷��
		void draw();

	private:
		Vector2 pos;                            // ���W
		std::vector<std::string> bgNameList;    // �w�i�̖��O�̃��X�g
		Sprite backGround;                      // �w�i�X�v���C�g
	};
}

#endif // !BACKGROUND_H
