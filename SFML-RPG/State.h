#include "Character.h"

class State
{
protected:
	sf::RenderWindow* window;
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keyBinds;
	std::stack<State*>* states;
	AudioComponent* audioComponent = nullptr;

	bool quit = false;

	float keytime;
	float keytimeMax;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	virtual void initKeybinds() = 0;
public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, 
		std::stack<State*>* states);
	virtual ~State();

	//Functions
	virtual void UpdateInput(const float& DeltaTime) = 0;
	virtual void Update(const float DeltaTime) = 0;
	virtual void UpdateKeytime(const float DeltaTime);
	virtual void UpdateMousePositions(const float DeltaTime);
	virtual void Render(sf::RenderTarget* target = nullptr) = 0;
	virtual void EndState();

	const bool& getQuit() { return this->quit; }
	const bool getKeytime();
};
 



