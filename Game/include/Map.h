#ifndef MAP_H
#define MAP_H

#include <array>
#include <string>
#include <vector>
#include "Lib.h"
#include "WindowInfo.h"
#include "../MapBlock.h"

namespace gnGame {

	using std::string;
	using std::array;
	class GameScene;
	class TutorialObject;
	
	// �}�b�v�̏����̕��ƍ���
	namespace MapInfo {
		constexpr int MaxMapWidth  = 100;	       // �}�b�v�̉��̐�
		constexpr int MaxMapHeight = 100;	       // �}�b�v�̏c�̐�
		constexpr int MapSize   = 32;          // �}�b�v�̃T�C�Y
		constexpr int MapHSize  = MapSize / 2; // �}�b�v�̔����̃T�C�Y
	};

	using MapField = array<array<MapBlock*, MapInfo::MaxMapWidth>, MapInfo::MaxMapHeight>;
	//using MapObjectList = std::vector<MapBlock*>;

	/// <summary>
	/// �}�b�v�N���X
	/// </summary>
	class Map {
	public:
		Map(GameScene* _gameScene);
		~Map();

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

		// �X�^�[�g�ʒu���擾
		Vector2 getStartPoint();

		// �}�b�v��ɃI�u�W�F�N�g��z�u����
		void setMapObjects(string _objName, const Vector2& _pos);

	private:
		int mapWidth;
		int mapHeight;
		GameScene* gameScene;
		MapField mapField;
		Vector2 startPoint;
		TextureSPtr mapTexture;
		TextureRegion textureRegion;
	};

};

#endif // !MAP_H