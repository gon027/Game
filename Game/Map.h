#ifndef MAP_H
#define MAP_H

#include "Lib.h"
#include <array>
#include <string>
#include "WindowInfo.h"

using std::string;
using std::array;

namespace gnGame {

	// �}�b�v�̏����̕��ƍ���
	namespace MapInfo {
		constexpr int MapWidth = 20;	         // �}�b�v�̉��̐�
		constexpr int MapHeight = 15;	         // �}�b�v�̏c�̐�
		constexpr int MapSize = 32;              // �}�b�v�̃T�C�Y
		constexpr int MapSizeHarf = MapSize / 2; // �}�b�v�̔����̃T�C�Y
	};

	// �}�b�v�̃^�C��
	enum class MAP_TILE {
		NONE,
		BLOCK,
		OBJECT,

	};

	class Map {
	public:
		~Map() = default;

		// �}�b�v��ǂݍ���
		void loadMapFile(const string& _fileName);

		// �}�b�v��`�悷��
		void drawMap();

		// �l��ݒ肷��
		void setTile(int _x, int _y, MAP_TILE _mapInfo);

		// �z����̒l���m�F����
		MAP_TILE getTile(int _x, int _y);

	private:
		int mapWidth;
		int mapHeight;
		array<array<int, MapInfo::MapWidth>, MapInfo::MapHeight> map;


		// �e�X�g�p�e�N�X�`��
		Texture block{ "Image/Test_Tile_Block.png" };
		Sprite sprite{ block };
	};

};


#endif // !MAP_H
