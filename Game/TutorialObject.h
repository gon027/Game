#ifndef TUTORIALOBJECT_H
#define TUTORIALOBJECT_H

#include "include/Lib.h"

namespace gnGame {

	// チュートリアル用のオブジェクトのクラス

	/// <summary>
	/// 移動のオブジェクト
	/// </summary>
	class MoveIntro : public Object{
	public:
		MoveIntro(const Vector2& _pos);
		~MoveIntro() = default;

		void update();

	private:
		Sprite sprite;
	};

	/// <summary>
	/// ジャンプのオブジェクト
	/// </summary>
	class JumpIntro : public Object {
	public:
		JumpIntro(const Vector2& _pos);
		~JumpIntro() = default;

		void update();

	private:
		Sprite sprite;
	};

	/// <summary>
	/// ショットのオブジェクト
	/// </summary>
	class ShotIntro : public Object {
	public:
		ShotIntro(const Vector2& _pos);
		~ShotIntro() = default;

		void update();

	private:
		Sprite sprite;
	};

}

#endif // !TUTORIALOBJECT_H