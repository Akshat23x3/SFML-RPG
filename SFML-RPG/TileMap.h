#pragma once
#include "Tile.h"
#include "stdafx.h"

class TileMap
{
	unsigned gridSizeU, gridSizeF, layers;
	sf::Vector2u maxSize;
	std::vector<std::vector<std::vector<Tile>>> tilemap;

public:
	TileMap();
	~TileMap();

	void Update(const float& DeltaTime);
	void Render(sf::RenderTarget* target);
};

