#pragma once

#include "stdafx.h"

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::Vector2f offset;

public:
	bool render = false;

	HitboxComponent(sf::Sprite& sprite, sf::Vector2f offset, sf::Vector2f size);
	~HitboxComponent();

	//Functions
	void Update(const float& DeltaTime);
	void Render(sf::RenderTarget* target);
	
	bool checkCollision(HitboxComponent* hitbox);

friend sf::RectangleShape getHitbox(HitboxComponent* hitboxComponent)
{
	return hitboxComponent->hitbox;
}
};
 
