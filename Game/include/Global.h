#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>

namespace gnGame {

	/// <summary>
	/// 定数などを定義する名前空間
	/// </summary>
	namespace global {

		namespace {
			// マップのフォルダパス
			static std::string MapFile = "Asset/MapData/";

			// 画像のフォルダパス
			static std::string ImageFile = "Asset/Image/";

			// 音楽のフォルダパス
			static std::string AudioPath = "Asset/BGM/";
		}

		// マップのフォルダパスを追加して返す
		static std::string MapAsset(const std::string& _map) {
			return MapFile + _map;
		}

		// 画像のフォルダパスを追加して返す
		static std::string ImageAsset(const std::string& _image) {
			return ImageFile + _image;
		}

		// 音楽のフォルダパスを追加して返す
		static std::string AudioAsset(const std::string& _audio) {
			return AudioPath + _audio;
		}
	}
}

#endif // !GLOBAL_H
