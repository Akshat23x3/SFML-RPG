#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->movementSpeed = 100.0f;

	this->movementComponent = NULL;
}

Entity::Entity(sf::RenderWindow* window)
{
	this->window = window;
}

Entity::~Entity()
{
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->hitboxComponent;
}

void Entity::setTexture(sf::Texture* texture)
{
	this->sprite.setTexture(*texture);
}

void Entity::createMovementComponent(float maxVelocity, float acceleration,
	float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration,
		deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(sprite, texture_sheet);
}

void Entity::createHitboxComponent(sf::Vector2f offset, sf::Vector2f size)
{
	this->hitboxComponent = new HitboxComponent(this->sprite, offset, size);
}

void Entity::setPosition(const float posX, const float posY)
{
	this->sprite.setPosition(sf::Vector2f(posX, posY));
}

void Entity::move(const float& DeltaTime, const float dirX, const float dirY)
{
	if (!this->movementComponent) return;

	this->movementComponent->move(dirX, dirY, DeltaTime);
}

void Entity::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	//if (!this->sprite) return;

	target->draw(this->sprite);

	if (this->hitboxComponent)
		this->hitboxComponent->Render(target);
}

void Entity::moveTo(const float& DeltaTime, const float posX, const float posY)
{
	float speedX = this->movementSpeed * (posX - this->sprite.getPosition().x) * DeltaTime;
	float speedY = this->movementSpeed * (posY - this->sprite.getPosition().y) * DeltaTime;

	this->sprite.move(sf::Vector2f(speedX, speedY));
}
void Entity::Update(const float& DeltaTime)
{
	if (this->movementComponent)
		this->movementComponent->Update(DeltaTime);
	
	if (this->hitboxComponent)
		this->hitboxComponent->Update(DeltaTime);
}

