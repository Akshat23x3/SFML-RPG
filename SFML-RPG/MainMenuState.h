#include "EditorState.h"

class MainMenuState :
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
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
		std::stack<State*>* states);

    virtual ~MainMenuState();

	//Functions
	void LoadTexture(std::string ImageLocation);
	void Update(const float DeltaTime);
	void UpdateButtons();
	void Render(sf::RenderTarget* target = nullptr);
	void UpdateInput(const float& DeltaTime);
};

