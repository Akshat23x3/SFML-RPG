#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration,
float deceleration) : 
	sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{
	
}

void MovementComponent::move(const float dirX, const float dirY, const float& DeltaTime)
{
	//Acceleration
	this->Velocity.x += dirX * this->acceleration;
	this->Velocity.y += dirY * this->acceleration;
}

void MovementComponent::Update(const float& DeltaTime)
{
	if (!this->isEnabled) 
	{ 
		this->Velocity = sf::Vector2f(0.0f, 0.0f);
		return;
	}

	//Acceleration Check
	if (this->Velocity.x > 0.0f)
	{
		if (this->Velocity.x > this->maxVelocity)
			this->Velocity.x = maxVelocity;

		this->Velocity.x -= deceleration;
		if (this->Velocity.x < 0.0f)
			this->Velocity.x = 0.0f;
	}
	if (this->Velocity.x < 0.0f)
	{
		if (-1 * this->Velocity.x > this->maxVelocity)
			this->Velocity.x = -1 * maxVelocity;

		this->Velocity.x += deceleration;
		if (this->Velocity.x > 0.0f)
			this->Velocity.x = 0.0f;
	}

	if (this->Velocity.y > 0.0f)
	{
		if (this->Velocity.y > this->maxVelocity)
			this->Velocity.y = maxVelocity;

		this->Velocity.y -= deceleration;
		if (this->Velocity.y < 0.0f)
			this->Velocity.y = 0.0f;
	}
	if (this->Velocity.y < 0.0f)
	{
		if (-1 * this->Velocity.y > this->maxVelocity)
			this->Velocity.y = -1 * maxVelocity;

		this->Velocity.y += deceleration;
		if (this->Velocity.y > 0.0f)
			this->Velocity.y = 0.0f;
	}

	//Final Move
	this->sprite.move(this->Velocity * DeltaTime);
}
