#pragma once
#include "stdafx.h"

class AudioComponent
{
private:
	sf::Music music;
	std::map<std::string, std::string> audios;

public:
	void Play(bool looping = false);
	void Stop();
	void initVariables();

	AudioComponent(const std::string& audioFile);
	~AudioComponent();
};

