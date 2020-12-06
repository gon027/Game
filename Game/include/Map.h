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
	
	// �}�b�v�̏����̕��ƍ���
	namespace MapInfo {
		constexpr int MaxMapWidth  = 100;	       // �}�b�v�̉��̐�
		constexpr int MaxMapHeight = 100;	       // �}�b�v�̏c�̐�
		constexpr int MapSize   = 32;          // �}�b�v�̃T�C�Y
		constexpr int MapHSize  = MapSize / 2; // �}�b�v�̔����̃T�C�Y
	};

	// �}�b�v�̃^�C��
	enum class MapTile {
		NONE   = 0,
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
		{}

		MapTile getTileType() {
			return tiletype;
		}

	private:
		MapTile tiletype;
	};

	using MapField = array<array<int, MapInfo::MaxMapWidth>, MapInfo::MaxMapHeight>;

	/// <summary>
	/// �}�b�v�N���X
	/// </summary>
	class Map {
	public:
		Map(Game* _gameScene);
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

		// �}�b�v���N���A����
		void claerMap();

		// �}�b�v�̃T�C�Y���擾����
		Vector2 getMapSize();

		// �X�^�[�g�ʒu��ݒ�
		Vector2 getStartPoint();

		// �}�b�v��ɃI�u�W�F�N�g��z�u����
		void setMapObjects(string _objName, const Vector2& _pos);

	private:
		Game* gameScene;
		MapField mapField;
		Vector2 startPoint;
		int mapWidth;
		int mapHeight;

		// �e�X�g�p�e�N�X�`��
		Sprite sprite;
		Sprite sprite2;
	};

};


#endif // !MAP_H
