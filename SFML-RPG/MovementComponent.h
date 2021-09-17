#pragma once

#include "stdafx.h"

class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f initialVelocity = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f Velocity;
	

	//Initializer Functions

public:
	bool isEnabled = true;

	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration,
		float deceleration);
	~MovementComponent();

	//Getters
	const sf::Vector2f& getVelocity() const { return this->Velocity; }

	void move(const float dirX, const float dirY, const float& DeltaTime);
	void Update(const float& DeltaTime);
};

