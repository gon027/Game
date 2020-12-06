#ifndef MAP_H
#define MAP_H

#include <array>
#include <string>
#include "Lib.h"
#include "WindowInfo.h"

namespace gnGame {

	using std::string;
	using std::array;
	class Game;
	
	// マップの初期の幅と高さ
	namespace MapInfo {
		constexpr int MaxMapWidth  = 100;	       // マップの横の数
		constexpr int MaxMapHeight = 100;	       // マップの縦の数
		constexpr int MapSize   = 32;          // マップのサイズ
		constexpr int MapHSize  = MapSize / 2; // マップの半分のサイズ
	};

	// マップのタイル
	enum class MapTile {
		NONE   = 0,
		BLOCK  = 1,
		OBJECT = 2,
	};

	/// <summary>
	/// マップのブロックのオブジェクト
	/// </summary>
	class MapBlock : public Object{
	public:
		MapBlock(MapTile _mapTile)
			: tiletype(_mapTile)
		{}

		MapTile getTileType() {
			return tiletype;
		}

	private:
		MapTile tiletype;
	};

	using MapField = array<array<int, MapInfo::MaxMapWidth>, MapInfo::MaxMapHeight>;

	/// <summary>
	/// マップクラス
	/// </summary>
	class Map {
	public:
		Map(Game* _gameScene);
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

		// マップをクリアする
		void claerMap();

		// マップのサイズを取得する
		Vector2 getMapSize();

		// スタート位置を設定
		Vector2 getStartPoint();

		// マップ上にオブジェクトを配置する
		void setMapObjects(string _objName, const Vector2& _pos);

	private:
		Game* gameScene;
		MapField mapField;
		Vector2 startPoint;
		int mapWidth;
		int mapHeight;

		// テスト用テクスチャ
		Sprite sprite;
		Sprite sprite2;
	};

};


#endif // !MAP_H
