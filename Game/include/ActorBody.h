#ifndef ACTORBODY_H
#define ACTORBODY_H

#include "Parameter.h"

namespace gnGame {

	/// <summary>
	/// アクターのパラメータを管理するクラス
	/// </summary>
	class ActorBody {
	public:
		ActorBody(const ActorParameter& _parameter);
		~ActorBody() = default;

		void setParameter(const ActorParameter& _parameter);

		void resetParameter();

		ActorParameter& getParameter();

		// ----- 回復系 -----

		// 体力を回復
		void healHp(float _hp);

		// MPを回復
		void healMp(float _mp);

		// ----- ダメージ系 -----

		// ダメージを与える
		void damage(float _damege);

		// mpを消費する
		void subMp(float _cost);

		// 現在パラメータのHPとMPしか使わないので、
		// 攻撃などは使うときに実装する

	private:
		const ActorParameter MaxParameter;  // 初期値
		ActorParameter parameter;           // 変動する
	};

}

#endif // !ACTORBODY_H
