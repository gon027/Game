#include "../include/Map.h"
#include "../include/GameScene.h"
#include "../include/Camera.h"
#include "../include/TextureManager.h"
#include "../include/EnemyManager.h"
#include "../include/EventManager.h"
#include "../include/ItemManager.h"
#include "../include/Item.h"
#include "../include/ShotEnemy.h"
#include "../include/WalkEnemy.h"
#include "../include/BigEnemy.h"
#include "../include/NomalEnemy.h"
#include "../include/BirdEnemy.h"
#include "../include/StageEvent.h"
#include "../include/GoalEvent.h"
#include "../TrapEvent.h"
#include "../include/Boss.h"
#include "../TutorialObject.h"
#include <fstream>
#include <sstream>
#include <vector>

#define IF(_objName, _name) if(_objName == _name)
#define ELIF(_objName, _name) else if(_objName == _name)

namespace gnGame {

	using std::fstream;

	namespace {
		constexpr int MAP_WIDTH = 12;
		constexpr int MAP_HEIGHT = 5;
		constexpr int MAPCHIP_SIZE = MAP_WIDTH * MAP_HEIGHT;
	}

	namespace utility {
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

	Map::Map(GameScene* _gameScene)
		: gameScene(_gameScene)
		, mapWidth(0)
		, mapHeight(0)
		, mapField()
		, mapTexture(TextureManager::getTexture("MapChip"))
	{
		textureRegion = Texture::spriteTexture(mapTexture, MAP_WIDTH, MAP_HEIGHT + 1);

		for (auto y{ 0 }; y < MapInfo::MaxMapHeight; ++y) {
			for (auto x{ 0 }; x < MapInfo::MaxMapWidth; ++x) {
				mapField[y][x] = nullptr;
			}
		}
	}

	Map::~Map()
	{
		for (int y = 0; y < MapInfo::MaxMapHeight; ++y) {
			for (int x = 0; x < MapInfo::MaxMapWidth; ++x) {
				if (mapField[y][x]) {
					delete mapField[y][x];
					mapField[y][x] = nullptr;
				}
			}
		}
	}

	void Map::loadMapFile(const string& _fileName)
	{
		fstream mapFile{ _fileName + ".txt" }, objFile{ _fileName + "_Obj.txt" };

		// マップファイルを読み込めなかったとき
		if (!mapFile) {
			exit(-1);
		}

		if (!objFile) {
			exit(-1);
		}

		string line;

		// 行と列の読み込み
		std::getline(mapFile, line);
		auto wh = utility::split(line);
		mapWidth = std::stoi(wh[0]);
		mapHeight = std::stoi(wh[1]);

		// マップの読み込み
		std::vector<std::vector<std::string>> vs;
		while (std::getline(mapFile, line)) {
			vs.emplace_back(utility::split(line));
		}

		// マップに値を設定する
		for (size_t y = 0; y < vs.size(); ++y) {
			for (size_t x = 0; x < vs[y].size(); ++x) {
				auto mTile = stoi(vs[y][x]);
				//mapField[y][x] = createMapBlock((MapTile)mTile);

				if (mTile >= 1 && mTile <= MAPCHIP_SIZE) {
					mapField[y][x] = createMapBlock(MapTile::BLOCK);
					mapField[y][x]->setTextureRect(textureRegion[mTile - 1]);
				}
				else if (mTile > MAPCHIP_SIZE + 1) {
					mapField[y][x] = createMapBlock(MapTile::OBJECT);
				}
				else {
					mapField[y][x] = createMapBlock(MapTile::NONE);
				}
			}
		}

		// オブジェクトの読み込み
		std::vector<std::vector<std::string>>objVec;
		while (std::getline(objFile, line)) {
			objVec.emplace_back(utility::split(line));
		}

		// オブジェクト配置
		for (size_t y = 0; y < objVec.size(); ++y) {
			auto vecX = static_cast<float>(stoi(objVec[y][1]));
			auto vecY = static_cast<float>(stoi(objVec[y][2]));
			setMapObjects(objVec[y][0], { vecX, vecY });
		}
		
		mapFile.close();
		objFile.close();
	}

	void Map::drawMap()
	{
		for (int y = 0; y < mapHeight; ++y) {
			for (int x = 0; x < mapWidth; ++x) {
				//if (mapField[y][x] == 0) continue;

				Vector2 pos{
					(float)(MapInfo::MapHSize + x * MapInfo::MapSize),
					(float)(MapInfo::MapHSize + y * MapInfo::MapSize)
				};

				// 画面外だと描画しない
				if (!Camera::isOnScreen(pos)) {
					continue;
				}

				auto screen = Camera::toScreenPos(pos);

				if (!mapField[y][x]) {
					continue;
				}

				mapField[y][x]->setPos(screen);
				mapField[y][x]->draw();				
			}
		}
	}

	void Map::setTile(int _x, int _y, MapTile _mapInfo)
	{
		delete mapField[_y][_x];
		mapField[_y][_x] = createMapBlock(MapTile::NONE);
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
		if (_x < 0 || _x >= mapWidth ||
			_y < 0 || _y >= mapHeight) 
		{
			return MapTile::NONE;
		}

		return mapField[_y][_x]->getMapTile();
	}

	void Map::claerMap()
	{
		for (int y = 0; y < MapInfo::MaxMapHeight; ++y) {
			for (int x = 0; x < MapInfo::MaxMapWidth; ++x) {
				if (mapField[y][x]) {
					delete mapField[y][x];
					mapField[y][x] = nullptr;
				}
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

	Vector2 Map::getStartPoint()
	{
		return startPoint;
	}

	void Map::setMapObjects(string _objName, const Vector2& _pos)
	{
		IF(_objName, "Start") {
			startPoint = _pos;
		}
		ELIF(_objName, "Goal") {
			auto e = EventPtr(new GoalEvent{ _pos, gameScene });
			EventManager::getIns()->addEvent(e);
		}
		ELIF(_objName, "StageEvent") {
			auto e = EventPtr(new StageEvent{ _pos, gameScene });
			EventManager::getIns()->addEvent(e);
		}
		ELIF(_objName, "Needle") {
			auto e = EventPtr(new TrapEvent{ _pos, gameScene });
			EventManager::getIns()->addEvent(e);
		}
		ELIF(_objName, "Enemy1") {
			EnemyPtr e = EnemyPtr(new ShotEnemy{ gameScene, _pos, {20, 100, 10, 45, 10} });
			e->setMap(this);
			e->onStart();
			EnemyManager::getIns()->addActor(e);
		}
		ELIF(_objName, "Enemy2") {
			EnemyPtr e = EnemyPtr(new WalkEnemy{ _pos, {20, 100, 10, 45, 10} });
			e->setMap(this);
			e->onStart();
			EnemyManager::getIns()->addActor(e);
		}
		ELIF(_objName, "Enemy3") {
			EnemyPtr e = EnemyPtr(new BigEnemy{ _pos, {100, 100, 10, 45, 10} });
			e->setMap(this);
			e->onStart();
			EnemyManager::getIns()->addActor(e);
		}
		ELIF(_objName, "Enemy4") {
			EnemyPtr e = EnemyPtr(new NomalEnemy{ _pos, {100, 100, 10, 45, 10} });
			e->setMap(this);
			e->onStart();
			EnemyManager::getIns()->addActor(e);
		}
		ELIF(_objName, "Enemy5") {
			EnemyPtr e = EnemyPtr(new BirdEnemy{ _pos, {100, 100, 10, 45, 10} });
			e->setMap(this);
			e->onStart();
			EnemyManager::getIns()->addActor(e);
		}
		ELIF(_objName, "Boss") {
			EnemyPtr e = EnemyPtr(new Boss{ gameScene, _pos, {500, 10, 10, 45, 10} });
			e->setMap(this);
			e->onStart();
			EnemyManager::getIns()->addActor(e);
		}
		ELIF(_objName, "Item1") {
			ItemPtr item = ItemPtr(new Item{ ItemType::HP });
			item->onStart();
			item->transform.setPos(_pos);
			ItemManager::getIns()->addItem(item);
		}
		ELIF(_objName, "Item2") {
			ItemPtr item = ItemPtr(new Item{ ItemType::MP });
			item->onStart();
			item->transform.setPos(_pos);
			ItemManager::getIns()->addItem(item);
		}
		ELIF(_objName, "Item3") {
			ItemPtr item = ItemPtr(new Item{ ItemType::Attack });
			item->onStart();
			item->transform.setPos(_pos);
			ItemManager::getIns()->addItem(item);
		}
		ELIF(_objName, "Item4") {
			ItemPtr item = ItemPtr(new Item{ ItemType::Defence });
			item->onStart();
			item->transform.setPos(_pos);
			ItemManager::getIns()->addItem(item);
		}
		ELIF(_objName, "Item5") {
			ItemPtr item = ItemPtr(new Item{ ItemType::Speed });
			item->onStart();
			item->transform.setPos(_pos);
			ItemManager::getIns()->addItem(item);
		}
		ELIF(_objName, "Move") {
			std::shared_ptr<TutorialObject> object{ new MoveIntro{_pos} };
			TutorialObjectList::getIns()->addObject(object);
		}
		ELIF(_objName, "Jump") {
			std::shared_ptr<TutorialObject> object{ new JumpIntro{_pos} };
			TutorialObjectList::getIns()->addObject(object);
		}
		ELIF(_objName, "Shot") {
			std::shared_ptr<TutorialObject> object{ new ShotIntro{_pos} };
			TutorialObjectList::getIns()->addObject(object);
		}
	}

	const MapBlock* Map::getMapBlock(int _index)
	{
		return mapObjectList[_index];
	}

	void Map::removeMapMapObject(int _index)
	{

	}

	MapObjectList& Map::getMapObjectList()
	{
		return mapObjectList;
	}
}