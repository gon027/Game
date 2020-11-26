#include "../include/PlayerBody.h"
#include "../include/Lib.h"

namespace gnGame {

	// Todo: 別のヘッダーファイルを作る
	namespace math {
		float clamp(float _value, float _min, float _max) {
			return min(_max, max(_value, _min));
		}
	}

	PlayerBody::PlayerBody()
		: PlayerBody({100.0f, 100.f, 10.0f, 10.0f, 10.0f})
	{
	}

	PlayerBody::PlayerBody(ActorParameter _parameter)
		: parameter(_parameter)
		, invincibleTime(0.0f)
		, isDamage(false)
		, bar()
	{
	}

	void PlayerBody::onUpdate()
	{
		if (isDamage) {
			invincibleTime += Time::deltaTime();

			if (invincibleTime >= 1.0f) {
				invincibleTime = 0.0f;
				isDamage = false;
			}
		}

		bar.onUpdate(parameter.hp, 100.0f);
	}

	void PlayerBody::setParamater(const ActorParameter& _parameter)
	{
		parameter = _parameter;
	}

	ActorParameter& PlayerBody::getParameter()
	{
		return parameter;
	}

	void PlayerBody::recoveryHp(float _hp)
	{
		parameter.hp = _hp;
	}

	void PlayerBody::recoveryMp(float _mp)
	{
		parameter.mp = _mp;
	}

	void PlayerBody::powerUp(float _power)
	{
		parameter.attack = _power;
	}

	void PlayerBody::defensPowerUp(float _defens)
	{
		parameter.defence = _defens;
	}

	void PlayerBody::speedUp(float _speed)
	{
		parameter.speed = _speed;
	}

	void PlayerBody::damage(int _damage)
	{
		if (isDamage) {
			return;
		}

		parameter.hp -= _damage;
		parameter.hp = math::clamp(parameter.hp, 0.f, 100.0f);
		isDamage = true;
	}
}
