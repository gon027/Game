#include "../include/TextureManager.h"

namespace gnGame {

	TextureMap TextureManager::textureMap{};

	void TextureManager::addTexture(const string& _name, const string& _filePath)
	{
		// textureMap�̒�����T���Č�����Ȃ������ꍇ�ǉ�����
		if (textureMap.find(_name) == textureMap.end()) {
			auto tex = Texture::createTexture(_filePath);
			textureMap.emplace(_name, tex);
		}
	}

	TextureSPtr& TextureManager::getTexture(const string& _textureName)
	{
		return textureMap[_textureName];
	}

}