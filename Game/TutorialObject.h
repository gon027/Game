#ifndef TUTORIALOBJECT_H
#define TUTORIALOBJECT_H

#include "include/Lib.h"
#include <vector>

namespace gnGame {

	// �`���[�g���A���p�̃I�u�W�F�N�g�̃N���X

	class TutorialObject : public Object{
	public:
		~TutorialObject() = default;

		virtual void onUpdate() = 0;
	};

	/// <summary>
	/// �ړ��̃I�u�W�F�N�g
	/// </summary>
	class MoveIntro : public TutorialObject {
	public:
		MoveIntro(const Vector2& _pos);
		~MoveIntro() = default;

		void onUpdate() override;

	private:
		Sprite sprite;
	};

	/// <summary>
	/// �W�����v�̃I�u�W�F�N�g
	/// </summary>
	class JumpIntro : public TutorialObject {
	public:
		JumpIntro(const Vector2& _pos);
		~JumpIntro() = default;

		void onUpdate() override;

	private:
		Sprite sprite;
	};

	/// <summary>
	/// �V���b�g�̃I�u�W�F�N�g
	/// </summary>
	class ShotIntro : public TutorialObject {
	public:
		ShotIntro(const Vector2& _pos);
		~ShotIntro() = default;

		void onUpdate() override;

	private:
		Sprite sprite;
	};

	using TutorialObjectPtr = std::shared_ptr<TutorialObject>;

	class TutorialObjectList {
	public:
		static TutorialObjectList* getIns();

	public:
		void addObject(TutorialObjectPtr _object);

		void update();

		void clear();

	private:
		TutorialObjectList() : tutorialObjectList() {};
		TutorialObjectList(const TutorialObjectList&);
		TutorialObjectList& operator= (const TutorialObjectList&);

	private:
		std::vector<TutorialObjectPtr> tutorialObjectList;
	};
}

#endif // !TUTORIALOBJECT_H