#ifndef HPBAR_H
#define HPBAR_H

#include "Lib.h"

namespace gnGame {

	class ParameterBar : public Object{
	public:
		ParameterBar();
		~ParameterBar() = default;

		// バーの更新
		void onUpdate(float _value, float maxSize);

	private:
		Rect rect;
	};
}

#endif // !HPBAR_H
