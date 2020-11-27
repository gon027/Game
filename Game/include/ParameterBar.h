#ifndef HPBAR_H
#define HPBAR_H

#include "Lib.h"

namespace gnGame {

	// �o�[�̃C���^�[�t�F�[�X
	class IParameterBar : public Object {
	public:
		virtual ~IParameterBar() = default;

		// �o�[�̍X�V
		virtual void onUpdate(float _x, float _y, float _value, float maxSize) = 0;
	};

	// �v���C���[��HP�o�[
	class HpBar : public IParameterBar {
	public:
		HpBar();
		~HpBar() = default;

		void onUpdate(float _x, float _y, float _value, float maxSize) override;

	private:
		Sprite back;      // �o�[�̔w�i
		Sprite barLine;   // �o�[�̉摜
	};

	// �v���C���[��MP�o�[
	class MpBar : public IParameterBar {
	public:
		MpBar();
		~MpBar() = default;

		void onUpdate(float _x, float _y, float _value, float maxSize) override;

	private:
		Sprite back;      // �o�[�̔w�i
		Sprite barLine;   // �o�[�̔w�i
	};
}

#endif // !HPBAR_H
