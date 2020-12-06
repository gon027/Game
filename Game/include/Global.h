#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>

namespace gnGame {

	/// <summary>
	/// �萔�Ȃǂ��`���閼�O���
	/// </summary>
	namespace global {

		namespace {
			// �}�b�v�̃t�H���_�p�X
			static std::string MapFile = "Asset/MapData/";

			// �摜�̃t�H���_�p�X
			static std::string ImageFile = "Asset/Image/";
		}

		// �}�b�v�̃t�H���_�p�X��ǉ����ĕԂ�
		static std::string MapAsset(const std::string& _map) {
			return MapFile + _map;
		}

		// �摜�̃t�H���_�p�X��ǉ����ĕԂ�
		static std::string ImageAsset(const std::string& _image) {
			return ImageFile + _image;
		}
	}
}

#endif // !GLOBAL_H