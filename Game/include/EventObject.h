#ifndef EVENTOBJECT_H
#define EVENTOBJECT_H

#include "Lib.h"

namespace gnGame {

	class GameScene;

	/// <summary>
	/// このオブジェクトに触ると、イベントが発火する
	/// </summary>
	class EventObject : public Object{
	public:
		EventObject(const Vector2& _pos, GameScene* _gameScene)
			: gameScene(_gameScene)
		{ 
			this->transform.pos.setPos(_pos);
		}

		virtual ~EventObject() = default;

		virtual void onUpdate() = 0;
		virtual void onEvent() = 0;

		virtual ICollider& getCollider() = 0;

	protected:
		GameScene* gameScene;
	};

}

#endif // !EVENTOBJECT_H
