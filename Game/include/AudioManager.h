#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <string>
#include <unordered_map>
#include "Lib.h"

namespace gnGame {

	using std::string;
	using AudioMap = std::unordered_map<std::string, std::shared_ptr<AudioSource>>;

	/// <summary>
	/// BGM, SE���Ǘ�����N���X
	/// </summary>
	class AudioManager {
	public:
		static AudioManager* getIns();

	public:
		// ���y�t�@�C����ǂݍ���
		void loadAudio(std::string _name, std::string _fileName);

		// ���y���Đ�����
		void play(std::string _name, PlayType _playType = PlayType::Nomal);

		// ���y���~����
		void stop(std::string _name);

		// �Đ��ʒu��ݒ肷��
		void setPosition(std::string _name, int _position);

	private:
		AudioManager() : audioMap() {};
		AudioManager(const AudioManager&);
		AudioManager& operator= (const AudioManager&);

	private:
		AudioMap audioMap;
	};

}

#endif // !AUDIOMANAGER_H
