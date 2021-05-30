#include "../include/TextureManager.h"
#include "../include/Global.h"

namespace gnGame {

	TextureMap TextureManager::textureMap{};

	void TextureManager::addTexture(const string& _name, const string& _filePath)
	{
		if (textureMap.find(_name) != textureMap.end()) {
			return;
		}

		// textureMap�̒�����T���Č�����Ȃ������ꍇ�ǉ�����
		auto tex = Texture::createTexture(global::ImageAsset(_filePath));
		textureMap.emplace(_name, tex);
	}

	TextureSPtr& TextureManager::getTexture(const string& _textureName)
	{
		return textureMap[_textureName];
	}

}