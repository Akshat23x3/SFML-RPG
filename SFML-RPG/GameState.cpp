#include "stdafx.h"
#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
	std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->window = window;
	this->initKeybinds();
	this->initTextures();
	this->initCharacters();
	this->initTileMap();
}

void GameState::initTileMap()
{
	this->map = new TileMap();
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/GameState_Keybinds.ini");


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
}



void GameState::initTextures()
{
	if (!this->textures["Player_IDLE"].loadFromFile("Data/Images/Sprites/Player/PLAYER_SHEET.png"))
		throw("ERROR::GAMESTATE::COULD NOT LOAD PLAYER_ANIMATION_TEXTURE");
}

void GameState::initCharacters()
{
	this->player = new Character(50, 50, &this->textures["Player_IDLE"], this->window);
}

void GameState::Update(const float DeltaTime)
{
	this->UpdateMousePositions(DeltaTime);
	this->UpdateInput(DeltaTime);
	this->map->Update(DeltaTime);
	this->player->Update(DeltaTime);
}

void GameState::Render(sf::RenderTarget* target)
{
	//this->map->Render(target);
	this->player->Render(target);
}

void GameState::UpdateInput(const float& DeltaTime)
{
	//Input
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)this->keyBinds.at("MOVE_RIGHT")))
		this->player->move(DeltaTime, 1.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)this->keyBinds.at("MOVE_LEFT")))
		this->player->move(DeltaTime, -1.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)this->keyBinds.at("MOVE_UP")))
		this->player->move(DeltaTime, 0.0f, -1.0f);
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)this->keyBinds.at("MOVE_DOWN")))
		this->player->move(DeltaTime, 0.0f, 1.0f);
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)this->keyBinds.at("PAUSE")))
	{
		this->states->push(new PauseMenuState(window, this->supportedKeys, this->states));
	}

	//if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)this->keyBinds.at("QUIT")))
	//	this->states->push(new MainMenuState(this->window, this->supportedKeys, this->states));
}