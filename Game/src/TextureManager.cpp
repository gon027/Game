#include "../include/TextureManager.h"

namespace gnGame {

	TextureMap TextureManager::textureMap{};

	void TextureManager::addTexture(const string& _name, const string& _filePath)
	{
		// textureMap‚Ì’†‚©‚ç’T‚µ‚ÄŒ©‚Â‚©‚ç‚È‚©‚Á‚½ê‡’Ç‰Á‚·‚é
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