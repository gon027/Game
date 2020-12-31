#ifndef PARAMETER_H
#define PARAMETER_H

namespace gnGame {

	// 各敵のパラメータ
	struct ActorParameter
	{
		float hp;        // 体力
		float mp;        // 技の力
		float attack;    // 攻撃力
		float defence;   // 守備力
		float speed;     // 速度
	};
}


#endif // !PARAMETER_H
