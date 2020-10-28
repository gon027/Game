#ifndef MAP_H
#define MAP_H

#include "Lib.h"
#include <array>
#include <string>
#include "WindowInfo.h"

using std::string;
using std::array;

namespace gnGame {

	// マップの初期の幅と高さ
	namespace MapInfo {
		constexpr int MapWidth = 20;	// マップの横の数
		constexpr int MapHeight = 15;	// マップの縦の数
		constexpr int MapSize = 32;
	};

	// マップのタイル
	enum MAP_TILE {
		NONE,
		BLOCK,
		OBJECT,
	};

	class Map {
	public:
		~Map() = default;

		// マップを読み込む
		void loadMapFile(const string& _fileName);

		// マップを描画する
		void drawMap();

		// 値を設定する
		void setTile(int _x, int _y, MAP_TILE _mapInfo);

		// 配列内の値を確認する
		MAP_TILE getTile(int _x, int _y);

	private:
		int mapWidth;
		int mapHeight;
		array<array<int, MapInfo::MapWidth>, MapInfo::MapHeight> map;
	};

};


#endif // !MAP_H
