#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <unordered_map>
#include <memory>
#include "Lib.h"

namespace gnGame {

	using std::string;
	using TexturePtr = std::shared_ptr<Texture>;
	using TextureMap = std::unordered_map<std::string, TextureSPtr>;

	// テクスチャ管理クラス
	class TextureManager {
	public:
		// テクスチャを追加する
		static void addTexture(const string& _name, const string& _filePath);

		// テクスチャを取得する
		static TextureSPtr& getTexture(const string& _textureName);

	private:
		static TextureMap textureMap;
	};

}

#endif // !TEXTUREMANAGER_H
