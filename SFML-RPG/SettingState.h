#pragma once
#include "GameState.h"
#include "GUI.h"

class SettingState :
    public State
{
private:
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Font font;
	std::map<std::string, sf::Text*> settings;
	std::map<std::string, GUI::Button*> buttons;
	std::map<std::string, GUI::SlideBox*> sliderBoxes;

	//Functions
	void initFonts();
	void initKeybinds();
	void initGUI();
	void initBackground();
	void initComponents();

public:

	SettingState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
		std::stack<State*>* states);

	virtual ~SettingState();

	//Functions
	void LoadTexture(std::string ImageLocation);
	void Update(const float DeltaTime);
	void UpdateButtons();
	void Render(sf::RenderTarget* target = nullptr);
	void UpdateInput(const float& DeltaTime);
};

