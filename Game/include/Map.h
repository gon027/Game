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

	// �}�b�v�̏����̕��ƍ���
	namespace MapInfo {
		constexpr int MapWidth  = 80;	       // �}�b�v�̉��̐�
		constexpr int MapHeight = 30;	       // �}�b�v�̏c�̐�
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

	// �}�b�v�^�C���̉摜
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

	private:
		int mapWidth  = 0;
		int mapHeight = 0;
		array<array<int, MapInfo::MapWidth>, MapInfo::MapHeight> map;
		MapData mapData;

		// �e�X�g�p�e�N�X�`��
		Texture block{ "Asset/Image/renga.png" };
		Sprite sprite{ block };
	};

};


#endif // !MAP_H
