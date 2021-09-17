#include "stdafx.h"
#include "GUI.h"
#include<iostream>



GUI::Button::Button(float posX, float posY, float width, float height, sf::Font* font, std::string text,
	sf::Color idleColorButton, sf::Color hoverColorButton, sf::Color activeColorButton,
	sf::Color idleColorText, sf::Color hoverColorText, sf::Color activeColorText)
{
	this->buttonState = Button_State::IDLE;

	this->idleColorButton = idleColorButton;
	this->hoverColorButton = hoverColorButton;
	this->activeColorButton = activeColorButton;
	this->idleColorText = idleColorText;
	this->hoverColorText = hoverColorText;
	this->activeColorText = activeColorText;

	this->shape.setPosition(sf::Vector2f(posX, posY));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(this->idleColorButton);

	this->font = font;

	this->text.setFont(*this->font);
	this->text.setCharacterSize(24);
	this->text.setString(text);
	
	this->text.setPosition(sf::Vector2f(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.0f) - (this->text.getGlobalBounds().width / 2.0f),
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.0f) - (this->text.getGlobalBounds().height / 2.0f)
	));	
}

GUI::Button::~Button()
{
}

//Accesors
const bool GUI::Button::isPressed()
{
	if (this->buttonState == Button_State::PRESSED)
	{
		return true;
	}

	return false;
}

//Functions
void GUI::Button::Update(const sf::Vector2f mousePos)
{
	/*Update the booleans*/
	this->buttonState = Button_State::IDLE;

	//Hovering
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = Button_State::HOVER;
												
		//Pressing
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			this->buttonState = Button_State::PRESSED;
		}
	}

	//system("cls");
	//std::cout << this->buttonState;

	switch (this->buttonState)
	{
	case Button_State::HOVER:
		this->shape.setFillColor(this->hoverColorButton);
		this->text.setFillColor(this->hoverColorText);
		break;

	case Button_State::PRESSED:
		this->shape.setFillColor(this->activeColorButton);
		this->text.setFillColor(this->activeColorText);
		break;

	default:
		this->shape.setFillColor(this->idleColorButton);
		this->text.setFillColor(this->idleColorText);
		break;
	}

}

void GUI::Button::Render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}


//SlideBoxList ================================

void GUI::SlideBox::initSlideBox()
{
	this->text.setFont(this->font);
	this->text.setCharacterSize(18);
	this->text.setString(this->contentList[this->currentIndex]);
	this->text.setPosition(sf::Vector2f(
		this->activeShape.getPosition().x + (this->activeShape.getGlobalBounds().width / 2.0f) - (this->text.getGlobalBounds().width / 2.0f),
		this->activeShape.getPosition().y + (this->activeShape.getGlobalBounds().height / 2.0f) - (this->text.getGlobalBounds().height / 2.0f)
	));
}

void GUI::SlideBox::initButtons()
{
	sf::Vector2f position = activeShape.getPosition();

	lButton = new Button(position.x - 20, position.y, 40, 40, &this->font, "<",
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
		sf::Color(230, 230, 230, 255), sf::Color(255), sf::Color(255));

	rButton = new Button(position.x + activeShape.getGlobalBounds().width, position.y, 40, 40, &this->font, ">",
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
		sf::Color(230, 230, 230, 255), sf::Color(255), sf::Color(255));
}

GUI::SlideBox::SlideBox(sf::Vector2f Position, sf::Vector2f Dimensions, sf::Font* font, sf::Color SliderColor,
	std::vector<std::string> contentList) : contentList(contentList), currentIndex(0)
{
	this->activeShape.setPosition(Position);
	this->activeShape.setSize(Dimensions);
	this->activeShape.setFillColor(SliderColor);

	this->font = *font;

	this->initButtons();
	this->initSlideBox();
	
}

GUI::SlideBox::~SlideBox()
{
	delete lButton;
	delete rButton;
}

void GUI::SlideBox::Update(const sf::Vector2f mousePos)
{
	this->UpdateButtons(mousePos);
	this->UpdateSlider();
}

void GUI::SlideBox::UpdateButtons(const sf::Vector2f mousePos)
{
	lButton->Update(mousePos);
	rButton->Update(mousePos);
}

void GUI::SlideBox::UpdateSlider()
{
	
	if (rButton->isPressed())
	{
		currentIndex++;
	}
	if (lButton->isPressed())
	{
		currentIndex--;
	}

	if (currentIndex > this->contentList.size() - 1)
		currentIndex = 0;
	if (currentIndex < 0)
		currentIndex = this->contentList.size() - 1;

	this->text.setString(this->contentList[currentIndex]);
}

void GUI::SlideBox::Render(sf::RenderTarget* target)
{
	this->rButton->Render(target);
	this->lButton->Render(target);
	target->draw(this->text);
}