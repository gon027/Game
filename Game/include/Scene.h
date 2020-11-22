#ifndef SCENE_H
#define SCENE_H

namespace gnGame {

	// �V�[���̊��N���X
	class IScene {
	public:
		virtual ~IScene() = default;

		// �ŏ��Ɏ��s�����֐�
		virtual void onStart() = 0;

		// �X�V�֐�
		virtual void onUpdate() = 0;

		// �Ō�Ɏ��s�����֐�
		virtual void onFinal() = 0;
	};
}

#endif // !SCENE_H
