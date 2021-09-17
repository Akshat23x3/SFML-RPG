#include "stdafx.h"
#include "SettingState.h"
#include <string>

SettingState::SettingState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
	std::stack<State*>* states)
	: State(window, supportedKeys, states)
{

	this->initFonts();
	this->initKeybinds();
	this->initBackground();
	//this->initComponents(); 
	this->initGUI();
}

SettingState::~SettingState()
{
	for (auto& it : buttons)
		delete it.second;

	for (auto& itr : this->sliderBoxes)
		delete itr.second;

	delete this->audioComponent;
}

void SettingState::initComponents()
{
	this->audioComponent = new AudioComponent("Config/SettingState_Audio.ini");
	this->audioComponent->Play(true);
}

void SettingState::initFonts()
{
	if (!this->font.loadFromFile("Data/Fonts/Dosis-Light.ttf"))
		throw("ERROR::SettingSTATE::COULD NOT LOAD FONT");
}

void SettingState::initKeybinds()
{
	std::ifstream ifs("Config/SettingState_Keybinds.ini");


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
		throw("ERROR::SettingSTATE::COULD NOT LOAD SettingState_Keybinds.ini");
	}
}

void SettingState::initGUI()
{
	std::ifstream ifs("Config/SettingState_Buttons.ini");

	std::map<std::string, std::vector<std::string>> settingsPanel;

	settingsPanel["Resolution"] = { "1920x1080", "1280x720", "800x600" };
	settingsPanel["Antialiasing"] = {"4x", "8x", "16x"};
	settingsPanel["Fullscreen"] = {"Enabled", "Disabled"};
	settingsPanel["FrameRateLimit"] = {"30", "60", "120"};
	settingsPanel["VerticalSync"] = {"Enabled", "Disabled"};

	if (ifs.is_open())
	{
		std::string key;
		int posXOffset = 0;
		int posYOffset = 70;
		int i = 0;
		while (ifs >> key)
		{
			if (key != "Apply")
			{
				this->sliderBoxes[key] = new GUI::SlideBox(sf::Vector2f(550, 400 + (i * posYOffset)), sf::Vector2f(120, 20),
					&this->font, sf::Color(20), settingsPanel[key]);
			}
			this->buttons[key] = new GUI::Button(400, 400 + (i * posYOffset), 100, 50, &this->font, key,
				sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
				sf::Color(230, 230, 230, 255), sf::Color(255), sf::Color(255));
			i++;
		}

		ifs.close();
	}
	else
		throw("ERROR::SettingSTATE::COULD NOT LOAD SettingState_Buttons.ini");
}


void SettingState::initBackground()
{
	this->LoadTexture("Data/Images/Backgrounds/bg2.png");
	this->background.setSize((sf::Vector2f)this->window->getSize());
	this->background.setTexture(&this->backgroundTexture);
}

void SettingState::LoadTexture(std::string ImageLocation)
{
	if (!this->backgroundTexture.loadFromFile(ImageLocation))
		throw("ERROR::SettingSTATE::COULD NOT LOAD " + ImageLocation);
}


void SettingState::Update(const float DeltaTime)
{
	this->UpdateMousePositions(DeltaTime);
	this->UpdateInput(DeltaTime);
	for(auto& itr : this->sliderBoxes)
		itr.second->Update((sf::Vector2f)this->mousePosWindow);
}

void SettingState::UpdateButtons()
{
	if (this->buttons.empty())
		return;
	for (auto& it : this->buttons)
		it.second->Update((sf::Vector2f)this->mousePosWindow);

	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)this->keyBinds.at("BACK")))
	{
		this->EndState();
	}

	if (this->buttons["Apply"]->isPressed())
	{
		std::string stringC = this->sliderBoxes["Resolution"]->getCurrentContent();
		sf::VideoMode Resolution;
		std::string content = "";
		for (int i = 0; i < stringC.length(); i++)
		{
			content += stringC[i];
			if (stringC[i] == 'x')
			{
				Resolution.width = std::atof(content.c_str());
				content = "";
			}
			else if (i == stringC.length() - 1)
			{
				Resolution.height = std::atof(content.c_str());
			}
		}

		stringC = this->sliderBoxes["Antialiasing"]->getCurrentContent();
		int antialiasing = 0;
		content = "";
		for (int i = 0; i < stringC.length(); i++)
		{
			content += stringC[i];
			if (stringC[i] == 'x')
			{
				antialiasing = std::atoi(content.c_str());
				content = "";
			}
		}

		stringC = this->sliderBoxes["Fullscreen"]->getCurrentContent();
		int Fullscreen = 0;
		if (stringC == "Enabled")
			Fullscreen = 1;
		else
			Fullscreen = 0;

		stringC = this->sliderBoxes["Fullscreen"]->getCurrentContent();
		int framerate = 0;
		framerate = std::atoi(stringC.c_str());

		stringC = this->sliderBoxes["Fullscreen"]->getCurrentContent();
		int vertical_sync = 0;
		if (stringC == "Enabled")
			vertical_sync = 1;
		else
			vertical_sync = 0;


		
		sf::ContextSettings windowSettings;
		
		//windowSettings.antialiasingLevel = antialiasing;
		//if (Fullscreen)
		//	this->window = new sf::RenderWindow(Resolution, "SFML C++ RPG",
		//		sf::Style::Fullscreen, windowSettings);
		//else
		//	this->window = new sf::RenderWindow(Resolution, "SFML C++ RPG",
		//		sf::Style::Titlebar | sf::Style::Close, windowSettings);

		this->window->setFramerateLimit(framerate);
		this->window->setVerticalSyncEnabled(vertical_sync);
	}
		
}

void SettingState::Render(sf::RenderTarget* target)
{
	target->draw(this->background);

	if (this->buttons.empty())
		return;
	for (auto& it : this->buttons)
		it.second->Render(target);

	for (auto& itr : this->sliderBoxes)
		itr.second->Render(target);
}

void SettingState::UpdateInput(const float& DeltaTime)
{
	this->UpdateButtons();
}