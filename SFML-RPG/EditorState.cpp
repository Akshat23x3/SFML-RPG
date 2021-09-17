
#include "stdafx.h"
#include "EditorState.h"

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
	std::stack<State*>* states)
	: State(window, supportedKeys, states)
{

	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	//this->initComponents();
}

EditorState::~EditorState()
{
	for (auto& it : buttons)
		delete it.second;
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Data/Fonts/Dosis-Light.ttf"))
		throw("ERROR::EditorState::COULD NOT LOAD FONT");
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/EditorState_Keybinds.ini");


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
		throw("ERROR::EditorState::COULD NOT LOAD EditorState_Keybinds.ini");
	}
}

void EditorState::initButtons()
{
	std::ifstream ifs("Config/EditorState_Buttons.ini");

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
		throw("ERROR::EditorState::COULD NOT LOAD EditorState_Buttons.ini");
}

void EditorState::Update(const float DeltaTime)
{
	this->UpdateMousePositions(DeltaTime);
	this->UpdateInput(DeltaTime);
}

void EditorState::UpdateButtons()
{
	if (this->buttons.empty())
		return;
	for (auto& it : this->buttons)
		it.second->Update((sf::Vector2f)this->mousePosWindow);

}

void EditorState::Render(sf::RenderTarget* target)
{
	//target->draw(this->background);

	if (this->buttons.empty())
		return;
	for (auto& it : this->buttons)
		it.second->Render(target);
}

void EditorState::UpdateInput(const float& DeltaTime)
{
	this->UpdateButtons();
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)this->keyBinds.at("PAUSE")))
	{
		this->states->push(new PauseMenuState(window, this->supportedKeys, this->states));
	}
}

void EditorState::EndState()
{
}
