#include "stdafx.h"
#include "Game.h"

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initKeys("Config/GameState_supportedKeys.ini");
    this->initStates();
}

Game::~Game()
{
    delete this->window;
    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

//Functions

void Game::initVariables()
{
    this->window = NULL;
    this->DeltaTime = 0.0f;
}

void Game::initGraphicsSettings()
{
    this->gfxSettings.loadFromFile("Config/window.ini");

}

//Initializer Functions
void Game::initWindow()
{  

    if (this->fullscreen)
        this->window = new sf::RenderWindow(window_bounds, title,
            sf::Style::Fullscreen, this->window_settings);
    else
        this->window = new sf::RenderWindow(window_bounds, title,
            sf::Style::Titlebar | sf::Style::Close, this->window_settings);
    this->window->setFramerateLimit(frameRateLimit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys(const std::string KeysFile)
{
    std::ifstream ifs(KeysFile);

    
    if (ifs.is_open())
    {
        std::string key; int key_value;
        while (!ifs.eof())
        {
            ifs >> key >> key_value;
            this->supportedKeys[key] = key_value;
        }
    }
    
    ifs.close();

}

void Game::UpdateStates()
{
    //Update the states
    if (!this->states.empty())
        this->states.top()->Update(this->DeltaTime);

    if (this->states.top()->getQuit())
    {
        if (this->states.size() == 1)
            this->window->close();

        delete this->states.top();
        this->states.pop();
    }
}

void Game::initStates()
{
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}



//Update Functions
void Game::UpdateDeltaTime()
{
    this->DeltaTime = this->DeltaTimeClock.restart().asSeconds();

    //system("cls");
    //std::cout << "DeltaTime : " << this->DeltaTime;
}

void Game::UpdateSFMLEvents()
{
    sf::Event event;
    while (this->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::Update()
{
    //Updating DeltaTime
    this->UpdateDeltaTime();

    //Update SFML Events
    this->UpdateSFMLEvents();

    //Update the states
    this->UpdateStates();
    
}

//Rendering Functions
void Game::Render()
{
    this->window->clear();

    //Render Shapes and Items
    if (!this->states.empty())
        this->states.top()->Render(window);

    this->window->display();
}

//Execution Functions
void Game::Run()
{
    
    while (window->isOpen())
    {
        this->Update();
        this->Render();
    }
}


