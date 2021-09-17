#include "stdafx.h"
#include "MainMenuState.h"


MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
	std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initBackground();
	this->initComponents();
}

MainMenuState::~MainMenuState()
{
	for (auto& it : buttons)
		delete it.second;

	this->audioComponent->Stop();
	delete audioComponent;
}

void MainMenuState::initComponents()
{
	this->audioComponent = new AudioComponent("Config/MainMenuState_Audio.ini");
	this->audioComponent->Play(true);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Data/Fonts/Dosis-Light.ttf"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/MainMenuState_Keybinds.ini");


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
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD MainMenuState_Keybinds.ini");
	}
}

void MainMenuState::initButtons()
{
	std::ifstream ifs("Config/MainMenuState_Buttons.ini");

	if (ifs.is_open())
	{
		std::string key;
		int posXOffset = 0;
		int posYOffset = 70;
		int i = 0;
		while (ifs >> key)
		{
			if (key == "Exit")
			{
				this->buttons[key] = new GUI::Button(400, 400 + ((i + 2) * posYOffset), 100, 50, &this->font, key,
					sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
					sf::Color(230, 230, 230, 255), sf::Color(255), sf::Color(255));
			}
			else
			{
				this->buttons[key] = new GUI::Button(400, 400 + (i * posYOffset), 100, 50, &this->font, key,
					sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
					sf::Color(230, 230, 230, 255), sf::Color(255), sf::Color(255));
			}
			
			i++;
		}

		ifs.close();
	}
	else
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD MainMenuState_Buttons.ini");
}


void MainMenuState::initBackground()
{
	this->LoadTexture("Data/Images/Backgrounds/bg2.png");
	this->background.setSize((sf::Vector2f)this->window->getSize());
	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::LoadTexture(std::string ImageLocation)
{
	if (!this->backgroundTexture.loadFromFile(ImageLocation))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD " + ImageLocation);
}


void MainMenuState::Update(const float DeltaTime)
{
	this->UpdateMousePositions(DeltaTime);
	this->UpdateInput(DeltaTime);
}

void MainMenuState::UpdateButtons()
{
	if (this->buttons.empty())
		return;
	for (auto& it : this->buttons) 
		it.second->Update((sf::Vector2f)this->mousePosWindow);

	if (this->buttons["Exit"]->isPressed())
	{
		this->EndState();
		this->window->close();
	}
		

	else if (this->buttons["New_Game"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
		this->EndState();
	}

	else if (this->buttons["Editor"]->isPressed())
	{
		this->states->push(new EditorState(this->window, this->supportedKeys, this->states));
		this->EndState();
	}

	else if (this->buttons["Settings"]->isPressed())
	{
		this->states->push(new SettingState(this->window, this->supportedKeys, this->states));
	}
		
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	target->draw(this->background);

	if (this->buttons.empty())
		return;
	for (auto& it : this->buttons)
		it.second->Render(target);
}

void MainMenuState::UpdateInput(const float& DeltaTime)
{
	this->UpdateButtons();
}