#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <memory>
#include <vector>
#include "Scene.h"

namespace gnGame {

	enum class SceneType {
		Title,     // �^�C�g���V�[��
		Select,    // �Z���N�g�V�[��
		Game,      // �Q�[���V�[��
	};

	class SceneManager {
	public:
		using ScenePtr = std::shared_ptr<IScene>;
		using SceneList = std::vector<ScenePtr>;
		using CurrentScene = std::weak_ptr<IScene>;

	public:
		SceneManager();
		~SceneManager() = default;

		// ������
		void initalize();

		// �X�V
		void update();

		// �Ō�̏���
		void finalize();

		// �V�[����؂�ւ���
		void changeScene(SceneType _sceneType);

	private:
		SceneList sceneList;        // �V�[����ۑ����郊�X�g
		CurrentScene currentScene;  // ���s���Ă���V�[��
		SceneType sceneType;        // ���݂̃V�[���̏��
	};
}


#endif // !SCENEMANAGER_H
