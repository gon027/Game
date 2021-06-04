#include "ActorBody.h"
#include "Lib.h"

namespace gnGame {
	ActorBody::ActorBody(const ActorParameter& _parameter)
		: MaxParameter(_parameter)
		, parameter(_parameter)
	{
	}

	void ActorBody::setParameter(const ActorParameter& _parameter)
	{
		parameter = _parameter;
	}

	void ActorBody::resetParameter()
	{
		parameter = MaxParameter;
	}

	ActorParameter& ActorBody::getParameter()
	{
		return parameter;
	}

	void ActorBody::healHp(float _hp)
	{
		parameter.hp += _hp;
		parameter.hp = clamp(parameter.hp, 0.0f, MaxParameter.hp);
	}

	void ActorBody::healMp(float _mp)
	{
		parameter.mp += _mp;
		parameter.mp = clamp(parameter.hp, 0.0f, MaxParameter.mp);
	}

	void ActorBody::damage(float _damege)
	{
		parameter.hp -= _damege;
		parameter.hp = clamp(parameter.hp, 0.0f, MaxParameter.hp);
	}

	void ActorBody::subMp(float _cost)
	{
		parameter.mp -= _cost;
		parameter.mp = clamp(parameter.hp, 0.0f, MaxParameter.mp);
	}
}