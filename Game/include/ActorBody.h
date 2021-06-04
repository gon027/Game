#ifndef ACTORBODY_H
#define ACTORBODY_H

#include "Parameter.h"

namespace gnGame {

	/// <summary>
	/// �A�N�^�[�̃p�����[�^���Ǘ�����N���X
	/// </summary>
	class ActorBody {
	public:
		ActorBody(const ActorParameter& _parameter);
		~ActorBody() = default;

		void setParameter(const ActorParameter& _parameter);

		void resetParameter();

		ActorParameter& getParameter();

		// ----- �񕜌n -----

		// �̗͂���
		void healHp(float _hp);

		// MP����
		void healMp(float _mp);

		// ----- �_���[�W�n -----

		// �_���[�W��^����
		void damage(float _damege);

		// mp�������
		void subMp(float _cost);

		// ���݃p�����[�^��HP��MP�����g��Ȃ��̂ŁA
		// �U���Ȃǂ͎g���Ƃ��Ɏ�������

	private:
		const ActorParameter MaxParameter;  // �����l
		ActorParameter parameter;           // �ϓ�����
	};

}

#endif // !ACTORBODY_H
