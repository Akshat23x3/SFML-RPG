#pragma once
class Tile
{
private:

protected:
	sf::RectangleShape shape;
public:
	Tile();
	Tile(float x, float y, float gridSizeF);
	~Tile();
	void Update(const float& DeltaTime);
	void Render(sf::RenderTarget* target);
};

