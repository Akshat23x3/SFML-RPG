#pragma once

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:

protected:
	sf::Sprite sprite;

	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;

	float movementSpeed = 100.0f;

	void initVariables();

public:
	sf::RenderWindow* window;

	Entity(sf::RenderWindow* window);
	virtual ~Entity();

	//Component Functions
	void setTexture(sf::Texture* texture);
	void createMovementComponent(float maxVelocity, float acceleration,
		float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createHitboxComponent(sf::Vector2f offset, sf::Vector2f size);

	//Functions
	virtual void setPosition(const float posX, const float posY);
	virtual void move(const float& DeltaTime, const float dirX, const float dirY);
	virtual void moveTo(const float& DeltaTime, const float posX, const float posY);
	virtual void Update(const float& DeltaTime);
	virtual void Render(sf::RenderTarget* target = nullptr);
};

