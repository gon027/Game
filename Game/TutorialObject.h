#ifndef TUTORIALOBJECT_H
#define TUTORIALOBJECT_H

#include "include/Lib.h"

namespace gnGame {

	// �`���[�g���A���p�̃I�u�W�F�N�g�̃N���X

	/// <summary>
	/// �ړ��̃I�u�W�F�N�g
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
	/// �W�����v�̃I�u�W�F�N�g
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
	/// �V���b�g�̃I�u�W�F�N�g
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