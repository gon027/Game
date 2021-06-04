#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "gnLib.h"

namespace gnLib {

	class GameObject : public Object {
	public:
		GameObject() : Object() {}
		virtual ~GameObject() = default;

		// �ŏ��ɌĂ΂��֐�
		virtual void onStart() = 0;

		// �X�V���ɌĂ΂��֐�
		virtual void onUpdate() = 0;

		// �`��֐�
		virtual void onDraw() = 0;
	};

}

#endif // !GAMEOBJECT_H
