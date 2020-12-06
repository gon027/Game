#include "../include/Map.h"
#include "../include/Camera.h"
#include "../include/TextureManager.h"
#include <fstream>
#include <sstream>
#include <vector>

using std::fstream;

namespace gnGame {

	namespace {
		std::vector<string> split(const string& _line) {
			vector<string> result;

			std::stringstream ss(_line);
			std::string item;
			while (std::getline(ss, item, ',')) {
				if (!item.empty()) {
					result.emplace_back(item);
				}
			}

			return result;
		}
	}

	Map::Map()
		: mapField()
		, mapWidth(0)
		, mapHeight(0)
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

		string line;

		// 行と列の読み込み
		std::getline(mapFile, line);
		auto wh = split(line);
		mapWidth = std::stoi(wh[0]);
		mapHeight = std::stoi(wh[1]);

		// マップの読み込み
		std::vector<std::vector<std::string>> vs;
		while (std::getline(mapFile, line)) {
			vs.emplace_back(split(line));
		}

		// マップに値を設定する
		for (size_t y = 0; y < vs.size(); ++y) {
			for (size_t x = 0; x < vs[y].size(); ++x) {
				mapField[y][x] = stoi(vs[y][x]);
			}
		}
		
		mapFile.close();
	}

	void Map::drawMap()
	{
		for (int y = 0; y < mapHeight; ++y) {
			for (int x = 0; x < mapWidth; ++x) {
				if (mapField[y][x] == 0) continue;

				Vector2 pos{
					(float)(MapInfo::MapHSize + x * MapInfo::MapSize),
					(float)(MapInfo::MapHSize + y * MapInfo::MapSize)
				};

				// 画面外だと描画しない
				if (!Camera::isOnScreen(pos)) {
					continue;
				}

				auto screen = Camera::toScreenPos(pos);

				switch (mapField[y][x])
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
		mapField[_y][_x] = static_cast<int>(_mapInfo);
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
		return (MapTile)mapField[_y][_x];
	}

	void Map::claerMap()
	{
		for (int y = 0; y < MapInfo::MaxMapHeight; ++y) {
			for (int x = 0; x < MapInfo::MaxMapWidth; ++x) {
				mapField[y][x] = 0;
			}
		}
	}

	Vector2 Map::getMapSize()
	{
		return {
			static_cast<float>(mapWidth) * MapInfo::MapSize,
			static_cast<float>(mapHeight) * MapInfo::MapSize
		};
	}

}