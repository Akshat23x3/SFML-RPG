#pragma once
#include "PauseMenuState.h"
#include "TileMap.h"

class GameState : public State
{
private:
	Character* player;
	TileMap* map;

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
		std::stack<State*>* states);

	//Functions
	void initTileMap();
	void initKeybinds();
	void initTextures();
	void initCharacters();
	void Update(const float DeltaTime);
	void Render(sf::RenderTarget* target = nullptr);
	void UpdateInput(const float& DeltaTime);
};

