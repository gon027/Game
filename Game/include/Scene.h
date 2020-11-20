#ifndef SCENE_H
#define SCENE_H

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

#endif // !SCENE_H
