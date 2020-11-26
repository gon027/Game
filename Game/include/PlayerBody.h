#ifndef PLAYERBODY_H
#define PLAYERBODY_H

#include "Parameter.h"

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
		void recoveryHp(int _hp);

		// MP���񕜂���
		void recoveryMp(int _mp);

		// �U���͂��グ��
		void powerUp(float _power);

		// ����͂��グ��
		void defensPowerUp(float _defens);

		// �X�s�[�h���グ��
		void speedUp(float _speed);

		// ----- �f�o�t�n -----

		// �_���[�W��^����
		void damage(int _damage);

	private:
		ActorParameter parameter;
		float invincibleTime;
		float isDamage;
	};

}

#endif // !PLAYERBODY_H
