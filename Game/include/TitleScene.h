#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "Lib.h"
#include "Scene.h"
#include "BackGround.h"

namespace gnGame {

	class SceneManager;

	class TitleUI {
	public:
		TitleUI();
		~TitleUI();

		void onStart();

		void onUpdate();

		void onFinal();

	private:
		Sprite backGround;
		Font text;
		Font title;   // �f�o�b�O�p�Ƃ��ăe�L�X�g��\���A�̂��ɉ摜�ɍ����ւ���
	};

	class TitleScene final : public IScene {
	public:
		TitleScene(SceneManager* _sceneManager);
		~TitleScene() = default;

		void onStart() override;

		void onUpdate() override;

		void onFinal() override;

	private:
		SceneManager* sceneManager;
		TitleUI titleUI;
		AudioSource titleBgm;
		AudioSource buttonSE;
	};
}

#endif // !TITLESCENE_H