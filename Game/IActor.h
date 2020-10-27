#ifndef IACTOR_H
#define IACTOR_H

// �L�����N�^�[�̊��N���X
class IActor {
public:
	~IActor() = default;

	virtual void onStart() = 0;
	virtual void onUpdate() = 0;
};

#endif // !IACTOR_H
