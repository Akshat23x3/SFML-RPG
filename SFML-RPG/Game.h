#pragma once

#include "MainMenuState.h"

class Game
{
private:
	class GraphicsSettings
	{
	public:
		GraphicsSettings()
		{
			this->resolution = sf::VideoMode::getDesktopMode();
			this->fullScreen = false;
			this->verticalSync = false;
			this->FrameRateLimit = 120.0;
			this->contextSettings.antialiasingLevel = 0;
			this->videoMode = sf::VideoMode::getFullscreenModes();
		}

		//Variables
		sf::VideoMode resolution;
		bool fullScreen;
		bool verticalSync;
		unsigned FrameRateLimit;
		sf::ContextSettings contextSettings;
		std::vector<sf::VideoMode> videoMode;

		void saveToFile(const std::string path)
		{
			 
		}
		void loadFromFile(const std::string path)
		{
			this->videoMode = sf::VideoMode::getFullscreenModes();

			std::ifstream ifs(path);

			std::string title = "None";
			sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
			unsigned frameRateLimit = 120;
			bool vertical_sync_enabled = false;
			unsigned antialiasing_level = 0;

			if (ifs.is_open()) //Open file if exists
			{
				std::getline(ifs, title);

				ifs >> window_bounds.width >> window_bounds.height;
				ifs >> this->fullScreen;
				ifs >> frameRateLimit;
				ifs >> vertical_sync_enabled;
				ifs >> antialiasing_level;
			}
			else
				std::cout << "File Does not exist";

			ifs.close(); //close the file

			this->contextSettings.antialiasingLevel = antialiasing_level;
		}
	};

	void UpdateDeltaTime();

	sf::RenderWindow* window;

	int WindowWidth, WindowHeight;

	sf::Clock DeltaTimeClock;

	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;

	GraphicsSettings gfxSettings;

public:
	
	Game();
	virtual ~Game();

	//Functions
	virtual void Update();
	virtual void Render();
	virtual void Run();
	virtual void UpdateSFMLEvents();

	//Initializers
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initStates();
	void initKeys(const std::string KeysFile);

	//Updates
	virtual void UpdateStates();

	//Variables
	float DeltaTime;
};


