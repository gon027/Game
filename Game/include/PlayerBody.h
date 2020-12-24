#ifndef PLAYERBODY_H
#define PLAYERBODY_H

#include "Parameter.h"
#include "ParameterBar.h"

namespace gnGame {

	/// <summary>
	/// プレイヤーのパラメータを管理するクラス
	/// 体力や攻撃力を保持する
	/// </summary>
	class PlayerBody {
	public:
		PlayerBody();
		PlayerBody(ActorParameter _parameter);
		~PlayerBody() = default;

		void onUpdate();

		void setParamater(const ActorParameter& _parameter);

		ActorParameter& getParameter();

		// ----- バフ系 -----

		// 体力を回復する
		void recoveryHp(float _hp);

		// MPを回復する
		void recoveryMp(float _mp);

		// 攻撃力を上げる
		void powerUp(float _power);

		// 守備力を上げる
		void defensPowerUp(float _defens);

		// スピードを上げる
		void speedUp(float _speed);

		// ----- デバフ系 -----

		// ダメージを与える
		void damage(float _damage);

		// mpを消費する
		void subMp(float _mp);

	private:
		ActorParameter parameter;
		HpBar hp;
		MpBar mp;
		float invincibleTime;
		float isDamage;
	};

}

#endif // !PLAYERBODY_H
