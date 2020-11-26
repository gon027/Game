#ifndef PARAMETER_H
#define PARAMETER_H

namespace gnGame {

	// �e�G�̃p�����[�^
	struct ActorParameter
	{
		float hp;          // �̗�
		float mp;          // �Z�̗�
		float attack;    // �U����
		float defence;   // �����
		float speed;     // ���x
	};

	// �e�����p�����[�^(�G��v���C���[�̍U���͂�ێ�����)
	struct BulletParameter
	{
		float attack;
	};
}


#endif // !PARAMETER_H
