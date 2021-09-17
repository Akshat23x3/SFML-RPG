#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, 
	sf::Vector2f offset,
	sf::Vector2f size) : sprite(sprite), offset(offset)
{
	this->hitbox.setPosition(this->sprite.getPosition() + this->offset);
	this->hitbox.setSize(size);
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.0f);
	this->hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{
}

void HitboxComponent::Update(const float& DeltaTime)
{
	this->hitbox.setPosition(this->sprite.getPosition() + this->offset);
}

void HitboxComponent::Render(sf::RenderTarget* target)
{
	if (!target || !render) return;

	target->draw(this->hitbox);
}

bool HitboxComponent::checkCollision(HitboxComponent* hitbox)
{
	return this->hitbox.getGlobalBounds().intersects(getHitbox(hitbox).getGlobalBounds());
}
