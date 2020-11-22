#ifndef PARAMETER_H
#define PARAMETER_H

namespace gnGame {

	// 各敵のパラメータ
	struct ActorParameter
	{
		int hp;          // 体力
		int mp;          // 技の力
		float attack;    // 攻撃力
		float defence;   // 守備力
		float speed;     // 速度
	};

	// 弾が持つパラメータ(敵やプレイヤーの攻撃力を保持する)
	struct BulletParameter
	{
		float attack;
	};
}


#endif // !PARAMETER_H
