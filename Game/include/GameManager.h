#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

namespace gnGame {

	class GameManager {
	public:
		// マネージャクラスの初期化
		static void initialize();

		// マネージャクラスの後処理
		static void finalize();
	};

}

#endif // !GAMEMANAGER_H
