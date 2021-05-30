#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <string>
#include <unordered_map>
#include "Lib.h"

namespace gnGame {

	using std::string;
	using AudioMap = std::unordered_map<std::string, std::shared_ptr<AudioSource>>;

	/// <summary>
	/// BGM, SEを管理するクラス
	/// </summary>
	class AudioManager {
	public:
		static AudioManager* getIns();

	public:
		// 音楽ファイルを読み込む
		void loadAudio(std::string _name, std::string _fileName);

		// 音楽を再生する
		void play(std::string _name, PlayType _playType = PlayType::Nomal);

		// 音楽を停止する
		void stop(std::string _name);

		// 再生位置を設定する
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
