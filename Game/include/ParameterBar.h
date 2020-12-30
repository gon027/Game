#ifndef HPBAR_H
#define HPBAR_H

#include "Lib.h"
#include "UIObject.h"

namespace gnGame {

	// バーのインターフェース
	class IParameterBar : public UIObject {
	public:
		virtual ~IParameterBar() = default;

		// バーの更新
		virtual void onUpdate(float _x, float _y, float _value, float maxSize) = 0;
	};

	// プレイヤーのHPバー
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
		Sprite back;      // バーの背景
		Sprite barLine;   // バーの画像
		Font numberFont;
		float value;
	};

	// プレイヤーのMPバー
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
		Sprite back;      // バーの背景
		Sprite barLine;   // バーの背景
		Font numberFont;
		float value;
	};
}

#endif // !HPBAR_H
