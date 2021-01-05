#ifndef STAGENUMBER_H
#define STAGENUMBER_H

namespace gnGame {

	// ステージの番号と解放されているステージを管理するクラス
	class StageManager {
	public:
		// ステージの最大数
		static const int MAXSTAGE{ 4 };

	public:
		static StageManager* getIns();

	public:
		// ステージをアンロックさせる
		void unlockStage();

		// アンロックされ散るステージを取得
		int getUnlockCurrentStage();

		// ステージ番号を1つ進める
		void incrementCurrentStage();

		// ステージ番号を1つ戻す
		void decrementCurrentStage();

		// 現在のステージ番号を取得する
		int getCurrentStage();

	private:
		StageManager() {};
		StageManager(const StageManager&);
		StageManager& operator= (const StageManager&);

	private:
		// 初期 : チュートリアルを含め２
		int UnlockCurrentStage{ 1 };

		// 現在のステージ
		int currentStage{ 0 };
	};

}

#endif // !STAGENUMBER_H