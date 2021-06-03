#ifndef STAGE_H
#define STAGE_H

#include <vector>
#include <string>
#include "BackGround.h"
#include "Map.h"

namespace gnGame {

	using std::vector;
	using std::string;

	class Player;

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

	/// <summary>
	/// チュートリアルステージ
	/// </summary>
	class TutorialStage final : public IStage {
	public:
		TutorialStage(Map* _map, Player* _player);
		~TutorialStage() = default;

		void onStart() override;
						
		void onUpdate() override;
						
		void onFinal() override;
						
		void initMap() override;
						
		void nextMap() override;
						
		void resetMap() override;

	private:
		vector<string> mapNameList;
		BackGround backGround;         // 背景
		Map* gameMap;                  // ゲームマップ
		Player* player;                // プレイヤーのポインタ
		int currentMapNumber;          // 現在のマップの番号
	};
	
	/// <summary>
	/// ステージ１
	/// </summary>
	class Stage1 final : public IStage {
	public:
		Stage1(Map* _map, Player* _player);
		~Stage1() = default;

		void onStart() override;

		void onUpdate() override;

		void onFinal() override;

		void initMap() override;

		void nextMap() override;

		void resetMap() override;

	private:
		vector<string> mapNameList;
		BackGround backGround;         // 背景
		Map* gameMap;                  // ゲームマップ
		Player* player;                // プレイヤーのポインタ
		int currentMapNumber;          // 現在のマップの番号
	};

	/// <summary>
	/// ステージ２
	/// </summary>
	class Stage2 final : public IStage {
	public:
		Stage2(Map* _map, Player* _player);
		~Stage2() = default;

		void onStart() override;

		void onUpdate() override;

		void onFinal() override;

		void initMap() override;

		void nextMap() override;

		void resetMap() override;
	private:
		vector<string> mapNameList;
		BackGround backGround;         // 背景
		Map* gameMap;                  // ゲームマップ
		Player* player;                // プレイヤーのポインタ
		int currentMapNumber;          // 現在のマップの番号
	};

	/// <summary>
	/// ボスステージ
	/// </summary>
	class BossStage final : public IStage {
	public:
		BossStage(Map* _map, Player* _player);
		~BossStage() = default;

		void onStart() override;

		void onUpdate() override;

		void onFinal() override;

		void initMap() override;

		void nextMap() override;

		void resetMap() override;

	private:
		vector<string> mapNameList;
		BackGround backGround;         // 背景
		Map* gameMap;                  // ゲームマップ
		Player* player;                // プレイヤーのポインタ
		int currentMapNumber;          // 現在のマップの番号
	};

	class DebugStage final : public IStage {
	public:
		DebugStage(Map* _map, Player* _player);
		~DebugStage() = default;

		void onStart() override;

		void onUpdate() override;

		void onFinal() override;

		void initMap() override;

		void nextMap() override;

		void resetMap() override;

	private:
		vector<string> mapNameList;
		BackGround backGround;         // 背景
		Map* gameMap;                  // ゲームマップ
		Player* player;                // プレイヤーのポインタ
		int currentMapNumber;          // 現在のマップの番号
	};


}

#endif // STAGE_H