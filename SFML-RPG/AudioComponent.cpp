#include "stdafx.h"
#include "AudioComponent.h"
#include <random>
#include<string>


void AudioComponent::Play(bool looping)
{
	srand(time(NULL));
	int randomIndex = rand() % this->audios.size();
	if (!this->music.openFromFile(this->audios[std::to_string(randomIndex)]))
	{
		std::cout << "ENGINE::ERROR::AUDIO::COULD NOT LOAD FILE " + this->audios[std::to_string(randomIndex)] << std::endl;
	}
	this->music.play();
}

void AudioComponent::Stop()
{
	this->music.stop();
}

void AudioComponent::initVariables()
{
}

AudioComponent::AudioComponent(const std::string& audioConfigFile)
{
	std::ifstream ifs(audioConfigFile);

	std::string index, audioFile;

	while (!ifs.eof())
	{
		ifs >> index >> audioFile;
		this->audios[index] = audioFile;
	}

	this->music.setVolume(60.0f);
}

AudioComponent::~AudioComponent()
{
	this->music.stop();
}

