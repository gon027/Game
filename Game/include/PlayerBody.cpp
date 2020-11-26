#include "PlayerBody.h"
#include "Lib.h"

namespace gnGame {

	PlayerBody::PlayerBody()
		: PlayerBody({100, 100, 10.0f, 10.0f, 10.0f})
	{
	}

	PlayerBody::PlayerBody(ActorParameter _parameter)
		: parameter(_parameter)
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
	}

	void PlayerBody::setParamater(const ActorParameter& _parameter)
	{
		parameter = _parameter;
	}

	ActorParameter& PlayerBody::getParameter()
	{
		return parameter;
	}

	void PlayerBody::recoveryHp(int _hp)
	{
		parameter.hp = _hp;
	}

	void PlayerBody::recoveryMp(int _mp)
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
		isDamage = true;
	}
}
