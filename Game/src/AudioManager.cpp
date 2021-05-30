#include "..\include\AudioManager.h"
#include "../include/Global.h"

namespace gnGame {

	AudioManager* AudioManager::getIns()
	{
		static AudioManager Instance;
		return &Instance;
	}

	void AudioManager::loadAudio(std::string _name, std::string _fileName)
	{
		if (audioMap.find(_name) != audioMap.end()) {
			return;
		}

		// �}�b�v�̒����猩����Ȃ������ꍇ�ǉ�����
		std::shared_ptr<AudioSource> source{ new AudioSource() };
		source->load(global::AudioAsset(_fileName));
		source->setVolume(-3000);
		audioMap.emplace(_name, source);
	}

	void AudioManager::play(std::string _name, PlayType _playType)
	{
		audioMap[_name]->play(_playType);
	}

	void AudioManager::stop(std::string _name)
	{
		audioMap[_name]->stop();
	}

	void AudioManager::setPosition(std::string _name, int _position)
	{
		audioMap[_name]->setPosition(_position);
	}

}