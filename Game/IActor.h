#ifndef IACTOR_H
#define IACTOR_H

// キャラクターの基底クラス
class IActor {
public:
	~IActor() = default;

	virtual void onStart() = 0;
	virtual void onUpdate() = 0;
};

#endif // !IACTOR_H
