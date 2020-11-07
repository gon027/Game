#ifndef ACTOR_H
#define ACTOR_H

#include "Lib.h"

namespace gnGame {

	struct IntersectPoints {
		static const int Size = 2;

		vector<Vector2> right;
		vector<Vector2> left;
		vector<Vector2> top;
		vector<Vector2> bottom;

		IntersectPoints()
			: right(Size)
			, left(Size)
			, top(Size)
			, bottom(Size)
		{}
	};

	// キャラクターの基底クラス
	class IActor : public Object {
	public:
		~IActor() = default;

		virtual void onStart() = 0;
		virtual void onUpdate() = 0;
	};

}

#endif // !ACTOR_H
