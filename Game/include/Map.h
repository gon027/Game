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
		constexpr int MapWidth  = 80;	       // マップの横の数
		constexpr int MapHeight = 30;	       // マップの縦の数
		constexpr int MapSize   = 32;          // マップのサイズ
		constexpr int MapHSize  = MapSize / 2; // マップの半分のサイズ
	};

	namespace WorldMapSize {
		constexpr int WorldMapWidth  = MapInfo::MapWidth * MapInfo::MapSize;
		constexpr int WorldMapHeight = MapInfo::MapHeight * MapInfo::MapSize;
	}


	// マップのタイル
	enum class MapTile {
		NONE   = -1,
		BLOCK  = 1,
		OBJECT = 2,
	};

	// マップタイルの画像
	struct MapData {
		MapData()
			: mapData("Asset/Image/MapData.png")
			, mapSprite(mapData)
			, spriteTexture(Texture::spriteTexture(mapData, 32, 32))
		{ }
		~MapData() = default;

		Texture mapData;
		Sprite mapSprite;
		vector<RECT> spriteTexture;
	};

	/// <summary>
	/// マップクラス
	/// </summary>
	class Map {
	public:
		Map();
		~Map() = default;

		// マップを読み込む
		void loadMapFile(const string& _fileName);

		// マップを描画する
		void drawMap();

		// 値を設定する
		void setTile(int _x, int _y, MapTile _mapInfo);

		// 地面となるタイルか調べる
		bool checkTile(int _x, int _y);

		// 配列内の値を確認する
		MapTile getTile(int _x, int _y);

	private:
		int mapWidth  = 0;
		int mapHeight = 0;
		array<array<int, MapInfo::MapWidth>, MapInfo::MapHeight> map;
		MapData mapData;

		// テスト用テクスチャ
		Texture block{ "Asset/Image/renga.png" };
		Sprite sprite{ block };
	};

};


#endif // !MAP_H
