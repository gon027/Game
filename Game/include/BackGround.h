#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector>
#include <string>
#include "Lib.h"

namespace gnGame {

	/// <summary>
	/// 背景クラス
	/// </summary>
	class BackGround {
	public:
		BackGround();
		~BackGround() = default;

		/// <summary>
		/// 背景の画像をセットする
		/// </summary>
		/// <param name="_index"> bgNameListの添え字番号 </param>
		void setTexture(int _index);

		// 描画する
		void draw();

	private:
		Vector2 pos;                            // 座標
		std::vector<std::string> bgNameList;    // 背景の名前のリスト
		Sprite backGround;                      // 背景スプライト
	};
}

#endif // !BACKGROUND_H
