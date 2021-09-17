#pragma once
#include "stdafx.h"

namespace GUI
{
	enum Button_State
	{
		IDLE = 0,
		HOVER,
		PRESSED	
	};

	class Button
	{
	private:
		short unsigned buttonState;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color idleColorButton, hoverColorButton, activeColorButton;
		sf::Color idleColorText, hoverColorText, activeColorText;

	public:
		Button(float posX, float posY, float width, float height, sf::Font* font, std::string text,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
			sf::Color idleColorText, sf::Color hoverColorText, sf::Color activeColorText);
		~Button();

		const bool isPressed();

		//Functions
		void Update(const sf::Vector2f mousePos);
		void Render(sf::RenderTarget* target);
	};

	class SlideBox
	{
	private:
		sf::RectangleShape activeShape;
		Button* lButton = nullptr;
		Button* rButton = nullptr;
		sf::Font font;
		sf::Text text;

		int currentIndex = 0;

		std::vector<std::string> contentList;

		//Initializer Functions
		void initSlideBox();
		void initButtons();

	public:
		SlideBox(sf::Vector2f Position, sf::Vector2f Dimensions, sf::Font* font, sf::Color SliderColor, 
			std::vector<std::string> contentList);

		~SlideBox();

		//Functions
		void Update(const sf::Vector2f mousePos);
		void UpdateButtons(const sf::Vector2f mousePos);
		void UpdateSlider();
		void Render(sf::RenderTarget* target);

		std::string getCurrentContent() { return this->contentList[this->currentIndex]; }
	};
}

