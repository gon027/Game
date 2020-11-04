#ifndef MAP_H
#define MAP_H

#include "Lib.h"
#include <array>
#include <string>
#include "WindowInfo.h"

using std::string;
using std::array;

namespace gnGame {

	class Camera;

	// マップの初期の幅と高さ
	namespace MapInfo {
		constexpr int MapWidth = 40;	         // マップの横の数
		constexpr int MapHeight = 15;	         // マップの縦の数
		constexpr int MapSize = 32;              // マップのサイズ
		constexpr int MapSizeHarf = MapSize / 2; // マップの半分のサイズ
	};

	// マップのタイル
	enum class MapTile {
		NONE   = -1,
		BLOCK  = 1,
		OBJECT = 2,
	};

	// マップタイルの画像
	class MapImage {

	};

	/// <summary>
	/// マップクラス
	/// </summary>
	class Map {
	public:
		Map(Camera* _camera);
		~Map() = default;

		// マップを読み込む
		void loadMapFile(const string& _fileName);

		// マップを描画する
		void drawMap();

		// 値を設定する
		void setTile(int _x, int _y, MapTile _mapInfo);

		// 配列内の値を確認する
		MapTile getTile(int _x, int _y);

	private:
		Camera* camera;

		int mapWidth;
		int mapHeight;
		array<array<int, MapInfo::MapWidth>, MapInfo::MapHeight> map;


		// テスト用テクスチャ
		Texture block{ "Image/Test_Tile_Block.png" };
		Sprite sprite{ block };
	};

};


#endif // !MAP_H
