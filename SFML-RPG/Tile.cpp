#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(float x, float y, float gridSizeF)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setPosition(sf::Vector2f(x, y));
}

Tile::~Tile()
{
}

void Tile::Update(const float& DeltaTime)
{
}

void Tile::Render(sf::RenderTarget* target)
{
	target->draw(shape);
}
