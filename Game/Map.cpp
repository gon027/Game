#include "Map.h"
#include "Camera.h"
#include <fstream>

using std::fstream;

namespace gnGame {

	Map::Map(Camera* _camera)
		: camera(_camera)
	{
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

				auto pos = Vector2{
					(float)(MapInfo::MapSizeHarf + x * MapInfo::MapSize),
					(float)(MapInfo::MapSizeHarf + y * MapInfo::MapSize)
				};

				auto screen = camera->toScreenPos(pos);

				sprite.setPos(screen);
				sprite.draw();
			}
		}

		/*
		for (int i = 0; i <= MapInfo::MapWidth; ++i) {
			Debug::drawLine(
				Vector2{ (float)(MapInfo::MapSize * i), 0 },
				Vector2{ (float)(MapInfo::MapSize * i), WindowInfo::WindowHeight },
				2.0f, Color::Blue
			);
		}

		for (int j = 0; j <= MapInfo::MapHeight; ++j) {
			Debug::drawLine(
				Vector2{ 0, (float)(MapInfo::MapSize * j)},
				Vector2{ WindowInfo::WindowWidth, (float)(MapInfo::MapSize * j)},
				2.0f, Color::Blue
			);
		}
		*/
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

}