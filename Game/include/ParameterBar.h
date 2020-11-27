#ifndef HPBAR_H
#define HPBAR_H

#include "Lib.h"

namespace gnGame {

	// バーのインターフェース
	class IParameterBar : public Object {
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

	private:
		Sprite back;      // バーの背景
		Sprite barLine;   // バーの画像
	};

	// プレイヤーのMPバー
	class MpBar : public IParameterBar {
	public:
		MpBar();
		~MpBar() = default;

		void onUpdate(float _x, float _y, float _value, float maxSize) override;

	private:
		Sprite back;      // バーの背景
		Sprite barLine;   // バーの背景
	};
}

#endif // !HPBAR_H
