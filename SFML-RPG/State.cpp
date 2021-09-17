#include "stdafx.h"
#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
	std::stack<State*>* states)
{
	this->states = states;
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->quit = false;
	this->keytime = 0.0f;
	this->keytimeMax = 10.0f;
}

State::~State()
{

}

void State::UpdateKeytime(const float DeltaTime)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.0f * DeltaTime;
}

void State::UpdateMousePositions(const float DeltaTime)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition());
}

void State::EndState()
{
	if(this->audioComponent) { this->audioComponent->Stop(); }
	this->quit = true;
}

const bool State::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.0f;
		return true;
	}
	return false;
}
