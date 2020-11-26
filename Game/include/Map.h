#ifndef MAP_H
#define MAP_H

#include <array>
#include <string>
#include "Lib.h"
#include "Grid.h"
#include "WindowInfo.h"

namespace gnGame {

	using std::string;
	using std::array;

	// �}�b�v�̏����̕��ƍ���
	namespace MapInfo {
		constexpr int MapWidth  = 80;	       // �}�b�v�̉��̐�
		constexpr int MapHeight = 35;	       // �}�b�v�̏c�̐�
		constexpr int MapSize   = 32;          // �}�b�v�̃T�C�Y
		constexpr int MapHSize  = MapSize / 2; // �}�b�v�̔����̃T�C�Y
	};

	namespace WorldMapSize {
		constexpr int WorldMapWidth  = MapInfo::MapWidth * MapInfo::MapSize;
		constexpr int WorldMapHeight = MapInfo::MapHeight * MapInfo::MapSize;
	}

	// �}�b�v�̃^�C��
	enum class MapTile {
		NONE   = -1,
		BLOCK  = 1,
		OBJECT = 2,
	};

	/// <summary>
	/// �}�b�v�̃u���b�N�̃I�u�W�F�N�g
	/// </summary>
	class MapBlock : public Object{
	public:
		MapBlock(MapTile _mapTile)
			: tiletype(_mapTile)
			, collider()
		{}

		MapTile getTileType() {
			return tiletype;
		}

		BoxCollider& getCollider() {
			return collider;
		}

	private:
		MapTile tiletype;
		BoxCollider collider;
	};

	/// <summary>
	/// �}�b�v�N���X
	/// </summary>
	class Map {
	public:
		Map();
		~Map() = default;

		// �}�b�v��ǂݍ���
		void loadMapFile(const string& _fileName);

		// �}�b�v��`�悷��
		void drawMap();

		// �l��ݒ肷��
		void setTile(int _x, int _y, MapTile _mapInfo);

		// �n�ʂƂȂ�^�C�������ׂ�
		bool checkTile(int _x, int _y);

		// �z����̒l���m�F����
		MapTile getTile(int _x, int _y);

		// ��ʊO�����肷��
		bool isOnScreen(const Vector2& _pos);

		// �}�b�v�̃T�C�Y���擾����
		Vector2 getMapSize();

	private:
		int mapWidth;
		int mapHeight;
		Grid grid;
		//array<array<int, MapInfo::MapWidth>, MapInfo::MapHeight> map;

		// �e�X�g�p�e�N�X�`��
		Sprite sprite;
		Sprite sprite2;
	};

};


#endif // !MAP_H
