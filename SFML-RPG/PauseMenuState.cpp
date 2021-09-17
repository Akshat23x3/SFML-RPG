#include "stdafx.h"
#include "PauseMenuState.h"
#include "MainMenuState.h"

PauseMenuState::PauseMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
	std::stack<State*>* states)
	: State(window, supportedKeys, states)
{

	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initBackground();
	this->initComponents();
}

PauseMenuState::~PauseMenuState()
{
	for (auto& it : buttons)
		delete it.second;

	delete this->audioComponent;
}

void PauseMenuState::initComponents()
{
	this->audioComponent = new AudioComponent("Config/PauseMenuState_Audio.ini");
	this->audioComponent->Play(true);
}

void PauseMenuState::initFonts()
{
	if (!this->font.loadFromFile("Data/Fonts/Dosis-Light.ttf"))
		throw("ERROR::PauseMenuSTATE::COULD NOT LOAD FONT");
}

void PauseMenuState::initKeybinds()
{
	std::ifstream ifs("Config/PauseMenuState_Keybinds.ini");


	if (ifs.is_open())
	{
		std::string key, key_bind;
		while (!ifs.eof())
		{
			ifs >> key >> key_bind;
			this->keyBinds[key] = this->supportedKeys->at(key_bind);
		}

		ifs.close();
	}
	else
	{
		throw("ERROR::PauseMenuSTATE::COULD NOT LOAD PauseMenuState_Keybinds.ini");
	}
}

void PauseMenuState::initButtons()
{
	std::ifstream ifs("Config/PauseMenuState_Buttons.ini");

	if (ifs.is_open())
	{
		std::string key;
		int posXOffset = 0;
		int posYOffset = 70;
		int i = 0;
		while (ifs >> key)
		{
			this->buttons[key] = new GUI::Button(400, 400 + (i * posYOffset), 100, 50, &this->font, key,
				sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
				sf::Color(230, 230, 230, 255), sf::Color(255), sf::Color(255));
			i++;
		}

		ifs.close();
	}
	else
		throw("ERROR::PauseMenuSTATE::COULD NOT LOAD PauseMenuState_Buttons.ini");
}


void PauseMenuState::initBackground()
{
	this->LoadTexture("Data/Images/Backgrounds/bg2.png");
	this->background.setSize((sf::Vector2f)this->window->getSize());
	this->background.setTexture(&this->backgroundTexture);
}

void PauseMenuState::LoadTexture(std::string ImageLocation)
{
	if (!this->backgroundTexture.loadFromFile(ImageLocation))
		throw("ERROR::PauseMenuSTATE::COULD NOT LOAD " + ImageLocation);
}


void PauseMenuState::Update(const float DeltaTime)
{
	this->UpdateMousePositions(DeltaTime);
	this->UpdateInput(DeltaTime);
}

void PauseMenuState::UpdateButtons()
{
	if (this->buttons.empty())
		return;
	for (auto& it : this->buttons)
		it.second->Update((sf::Vector2f)this->mousePosWindow);

	if (this->buttons["Resume"]->isPressed())
	{
		this->EndState();
	}
	if (this->buttons["Settings"]->isPressed())
	{
		this->states->push(new SettingState(this->window, this->supportedKeys, this->states));
	}
	if (this->buttons["Quit_To_Desktop"]->isPressed())
	{
		this->EndState();
		this->window->close();
	}
	if (this->buttons["Quit_To_Menu"]->isPressed())
	{
		this->EndState();
		this->states->push(new MainMenuState(this->window, this->supportedKeys, this->states));
	}

}

void PauseMenuState::Render(sf::RenderTarget* target)
{
	target->draw(this->background);

	if (this->buttons.empty())
		return;
	for (auto& it : this->buttons)
		it.second->Render(target);
}

void PauseMenuState::UpdateInput(const float& DeltaTime)
{
	this->UpdateButtons();
}