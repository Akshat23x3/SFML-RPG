#pragma once
#include "State.h"
#include "GUI.h"
class PauseMenuState :
    public State
{
private:
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Font font;
	std::map<std::string, GUI::Button*> buttons;

	//Functions
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initBackground();
	void initComponents();

public:

	PauseMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
		std::stack<State*>* states);

	virtual ~PauseMenuState();

	//Functions
	void LoadTexture(std::string ImageLocation);
	void Update(const float DeltaTime);
	void UpdateButtons();
	void Render(sf::RenderTarget* target = nullptr);
	void UpdateInput(const float& DeltaTime);

};

