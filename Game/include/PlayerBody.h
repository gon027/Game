#ifndef PLAYERBODY_H
#define PLAYERBODY_H

#include "Parameter.h"
#include "ParameterBar.h"

namespace gnGame {

	/// <summary>
	/// �v���C���[�̃p�����[�^���Ǘ�����N���X
	/// �̗͂�U���͂�ێ�����
	/// </summary>
	class PlayerBody {
	public:
		PlayerBody();
		PlayerBody(ActorParameter _parameter);
		~PlayerBody() = default;

		void onUpdate();

		void setParamater(const ActorParameter& _parameter);

		ActorParameter& getParameter();

		// ----- �o�t�n -----

		// �̗͂��񕜂���
		void setHP(float _hp);

		// MP���񕜂���
		void setMP(float _mp);

		// �U���͂��グ��
		void setAttack(float _power);

		// ����͂��グ��
		void setDefence(float _defens);

		// �X�s�[�h���グ��
		void setSpeed(float _speed);

		// ----- �f�o�t�n -----

		// �_���[�W��^����
		void damage(float _damage);

		// mp�������
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
