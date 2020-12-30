#ifndef HPBAR_H
#define HPBAR_H

#include "Lib.h"
#include "UIObject.h"

namespace gnGame {

	// �o�[�̃C���^�[�t�F�[�X
	class IParameterBar : public UIObject {
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

		void OnDraw() override;

	private:
		Vector2 barPos;
		Vector2 barLinePos;
		Vector2 barLineScale;
		Sprite back;      // �o�[�̔w�i
		Sprite barLine;   // �o�[�̉摜
		Font numberFont;
		float value;
	};

	// �v���C���[��MP�o�[
	class MpBar : public IParameterBar {
	public:
		MpBar();
		~MpBar() = default;

		void onUpdate(float _x, float _y, float _value, float maxSize) override;

		void OnDraw() override;

	private:
		Vector2 barPos;
		Vector2 barLinePos;
		Vector2 barLineScale;
		Sprite back;      // �o�[�̔w�i
		Sprite barLine;   // �o�[�̔w�i
		Font numberFont;
		float value;
	};
}

#endif // !HPBAR_H
