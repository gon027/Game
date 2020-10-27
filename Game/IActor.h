#ifndef IACTOR_H
#define IACTOR_H

#include "Lib.h"

// キャラクターの基底クラス
class IActor : public Object{
public:
	~IActor() = default;

	virtual void onStart() = 0;
	virtual void onUpdate() = 0;
};

#endif // !IACTOR_H
