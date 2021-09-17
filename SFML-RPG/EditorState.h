#include "SettingState.h"
#include "Tile.h"
#include "GUI.h"

class EditorState :
    public State
{
private:
	sf::Font font;
	std::map<std::string, GUI::Button*> buttons;
	std::map<std::string, std::vector<Tile*>> tiles;

	void initFonts();
	void initKeybinds();
	void initButtons();
	//void initComponents();

public:
	EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
		std::stack<State*>* states);

	virtual ~EditorState();

	//Functions
	void Update(const float DeltaTime);
	void UpdateButtons();
	void Render(sf::RenderTarget* target = nullptr);
	void UpdateInput(const float& DeltaTime);
	void EndState();
};

