#ifndef TUTORIALOBJECT_H
#define TUTORIALOBJECT_H

#include "include/Lib.h"
#include <vector>

namespace gnGame {

	// チュートリアル用のオブジェクトのクラス

	class TutorialObject : public Object{
	public:
		~TutorialObject() = default;

		virtual void onUpdate() = 0;
	};

	/// <summary>
	/// 移動のオブジェクト
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
	/// ジャンプのオブジェクト
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
	/// ショットのオブジェクト
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