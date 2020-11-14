#ifndef STAGE_H
#define STAGE_H

namespace gnGame {

	// ステージの基底クラス
	class IStage {
	public:
		virtual ~IStage() = default;
	private:
		int a = 10;
	};

}

#endif // !STAGE_H
