#ifndef STAGE_H
#define STAGE_H

namespace gnGame {

	class IStage {
	public:
		virtual ~IStage() = default;

		virtual void onStart() = 0;

		virtual void onUpdate() = 0;

		virtual void onFinal() = 0;

		// 最初に呼ばれるマップの初期化
		virtual void initMap() = 0;

		// 次のマップに移動
		virtual void nextMap() = 0;

		// マップをリセットする
		virtual void resetMap() = 0;
	};

	class TutorialStage final : public IStage {
	
	};
	
	class Stage1 final : public IStage {
	
	};

	class Stage2 final : public IStage {
	
	};

	class BossStage final : public IStage {


	};

}

#endif // STAGE_H