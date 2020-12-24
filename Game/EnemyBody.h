#ifndef ENEMYBODY_H
#define ENEMYBODY_H

#include "include/Parameter.h"

namespace gnGame {

	/// <summary>
	/// �G�̃p�����[�^���Ǘ�����N���X
	/// </summary>
	class EnemyBody {
	public:
		EnemyBody(const ActorParameter& _parameter);
		~EnemyBody() = default;

		void setParameter(const ActorParameter& _parameter);

		ActorParameter& getParameter();

		// �_���[�W
		void damage(int _damage);

	private:
		ActorParameter parameter;
	};
}

#endif // !ENEMYBODY_H