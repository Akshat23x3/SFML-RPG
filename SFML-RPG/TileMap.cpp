#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap()
{
	this->gridSizeF = 50.0f;
	this->gridSizeU = (unsigned)this->gridSizeF;
	this->maxSize.x = 100;
	this->maxSize.y = 100;
	this->layers = 1;

	this->tilemap.resize(this->maxSize.x); 
	for (int x = 0; x < this->maxSize.x; x++)
	{
		this->tilemap.push_back(std::vector<std::vector<Tile>>());
		for (int y = 0; y < this->maxSize.y; y++)
		{
			this->tilemap.resize(this->maxSize.y);
			this->tilemap[x].push_back(std::vector<Tile>());

			for (int z = 0; z < this->layers; z++)
			{
				this->tilemap[x][y].resize(this->layers);
				this->tilemap[x][y].push_back(Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF));
			}
		}
	}
	
}

TileMap::~TileMap()
{
}

void TileMap::Update(const float& DeltaTime)
{
	for (auto& x : this->tilemap)
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				z.Update(DeltaTime);
			}
		}
	}
}

void TileMap::Render(sf::RenderTarget* target)
{
	for (auto& x : this->tilemap)
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				z.Render(target);
			}
		}
	}
}