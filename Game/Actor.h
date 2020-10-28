#ifndef ACTOR_H
#define ACTOR_H

#include "Lib.h"

namespace gnGame {

	// �L�����N�^�[�̊��N���X
	class IActor : public Object {
	public:
		~IActor() = default;

		virtual void onStart() = 0;
		virtual void onUpdate() = 0;
	};

}

#endif // !ACTOR_H
