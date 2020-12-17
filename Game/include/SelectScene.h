#ifndef SELECTSCENE_H
#define SELECTSCENE_H

#include "Scene.h"
#include "BackGround.h"

namespace gnGame {

	class SceneManager;

	// �Z���N�g�V�[����UI�N���X
	class SelectSceneUI {
	public:
		SelectSceneUI();
		~SelectSceneUI();

		void onStart();

		void onUpdate();

		void onFinal();

		// �v���C���[����̃X�e�[�W�̑�����󂯕t����
		void stageSelect();

	private:
		Sprite backGround;            // �w�i
		Sprite number;                // �X�e�[�W�摜
		Sprite frame;                 // �t���[��
		TextureRegion textureRegion;  // �X�e�[�W�ԍ��̉摜�̋�Ԃ𕪊������z��
	};

	// �Z���N�g�V�[���N���X
	class SelectScene final : public IScene {
	public:
		SelectScene(SceneManager* _sceneManager);
		~SelectScene() = default;

		void onStart() override;

		void onUpdate() override;

		void onFinal() override;

	private:
		SceneManager* sceneManager;
		SelectSceneUI selectSceneUI;
	};
}

#endif // !SELECTSCENE_H