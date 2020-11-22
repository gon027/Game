#include "../include/Map.h"
#include "../include/Camera.h"
#include "../include/TextureManager.h"
#include <fstream>

using std::fstream;

namespace gnGame {

	Map::Map()
		: map()
		, sprite()
		, sprite2()
	{
		sprite.setTexture(TextureManager::getTexture("Block"));
		sprite2.setTexture(TextureManager::getTexture("floor"));
	}

	void Map::loadMapFile(const string& _fileName)
	{
		fstream mapFile{ _fileName };

		// マップファイルを読み込めなかったとき
		if (!mapFile) {
			exit(-1);
		}

		int my = 0;
		string line;
		while (std::getline(mapFile, line)) {

			int mx = 0;
			for (int x = 0; x < line.size(); ++x) {
				if (line[x] == ',') continue;

				map[my][mx] = line[x] - '0';
				++mx;
			}

			++my;
		}

		mapFile.close();
	}

	void Map::drawMap()
	{
		for (int y = 0; y < MapInfo::MapHeight; ++y) {
			for (int x = 0; x < MapInfo::MapWidth; ++x) {
				if (map[y][x] == 0) continue;

				Vector2 pos{
					(float)(MapInfo::MapHSize + x * MapInfo::MapSize),
					(float)(MapInfo::MapHSize + y * MapInfo::MapSize)
				};

				// 画面外だと描画しない
				if (!isOnScreen(pos)) {
					continue;
				}

				auto screen = Camera::toScreenPos(pos);

				switch (map[y][x])
				{
				case 1:
					sprite.draw(screen, Vector2::One, 0.0f);
					break;
				case 2:
					sprite2.draw(screen, Vector2::One, 0.0f);
					break;
				default:
					break;
				}
				
			}
		}
	}

	void Map::setTile(int _x, int _y, MapTile _mapInfo)
	{
		map[_y][_x] = (int)_mapInfo;
	}

	bool Map::checkTile(int _x, int _y)
	{
		auto tile = getTile(_x / 32, _y / 32);

		switch (tile)
		{
		case gnGame::MapTile::NONE:
			return false;
			break;
		case gnGame::MapTile::BLOCK:
			return true;
			break;
		case gnGame::MapTile::OBJECT:
			return true;
			break;
		default:
			return false;
			break;
		}

		return false;
	}

	MapTile Map::getTile(int _x, int _y)
	{
		// 配列外の添え字を渡されたらNoneを返す
		if (_x >= MapInfo::MapWidth || _x < 0 
			|| _y >= MapInfo::MapHeight || _y < 0) {
			return MapTile::NONE;
		}

		return (MapTile)map[_y][_x];
	}

	bool Map::isOnScreen(const Vector2& _pos)
	{
		auto minScrenn = Camera::minScreenPos();
		auto maxScreen = Camera::maxScreenPos();

		return _pos.x + 32.0f >= minScrenn.x && _pos.x - 32.0f <= maxScreen.x
			&& _pos.y + 32.0f >= minScrenn.y && _pos.y - 32.0f <= maxScreen.y;

	}

}