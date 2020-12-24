#ifndef ENEMYBODY_H
#define ENEMYBODY_H

#include "Parameter.h"

namespace gnGame {

	/// <summary>
	/// 敵のパラメータを管理するクラス
	/// </summary>
	class EnemyBody {
	public:
		EnemyBody(const ActorParameter& _parameter);
		~EnemyBody() = default;

		void setParameter(const ActorParameter& _parameter);

		ActorParameter& getParameter();

		// ダメージ
		void damage(float _damage);

	private:
		ActorParameter parameter;
	};
}

#endif // !ENEMYBODY_H