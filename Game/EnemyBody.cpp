#include "EnemyBody.h"
#include "include/Lib.h"

namespace gnGame {

	EnemyBody::EnemyBody(const ActorParameter& _parameter)
		: parameter(_parameter)
	{

	}

	void EnemyBody::setParameter(const ActorParameter& _parameter)
	{
		parameter = _parameter;
	}

	ActorParameter& EnemyBody::getParameter()
	{
		return parameter;
	}

	void EnemyBody::damage(int _damage)
	{
		parameter.hp -= _damage;
		parameter.hp = clamp(parameter.hp, 0.f, 100.0f);
	}

}