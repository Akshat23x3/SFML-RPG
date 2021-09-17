#include "stdafx.h"
#include "Character.h"

void Character::initVariables()
{
	//this->sprite.setScale(sf::Vector2f(2.0f, 2.0f));
	this->isAttacking = false;
}

Character::Character(float posX, float posY, sf::Texture* texture_sheet, sf::RenderWindow* window) :
	Entity(window)
{
	this->initVariables();

	this->setPosition(posX, posY);

	this->createMovementComponent(350.0f, 12.0f, 5.0f);
	this->createAnimationComponent(*texture_sheet);
	this->createHitboxComponent(sf::Vector2f(86.0f, 70.f), sf::Vector2f(86.0f, 111.0f));
	//this->createHitboxComponent(sf::Vector2f(20.0f, 10.0f), sf::Vector2f(85.0f, 110.0f));
	this->hitboxComponent->render = true;

	//this->animationComponent->addAnimation("IDLE", 8, sf::Vector2i(0, 0), sf::Vector2i(8, 0), sf::Vector2i(64, 64));
	//this->animationComponent->addAnimation("WALK_LEFT", 8, sf::Vector2i(4, 1), sf::Vector2i(7, 1), sf::Vector2i(64, 64));
	//this->animationComponent->addAnimation("WALK_RIGHT", 8, sf::Vector2i(8, 1), sf::Vector2i(11, 1), sf::Vector2i(64, 64));
	//this->animationComponent->addAnimation("WALK_UP", 8, sf::Vector2i(12, 1), sf::Vector2i(15, 1), sf::Vector2i(64, 64));
	//this->animationComponent->addAnimation("WALK_DOWN", 8, sf::Vector2i(0, 1), sf::Vector2i(3, 1), sf::Vector2i(64, 64));

	this->animationComponent->addAnimation("IDLE", 8, sf::Vector2i(0, 0), sf::Vector2i(13, 0), sf::Vector2i(192, 192));
	this->animationComponent->addAnimation("WALK_LEFT", 15, sf::Vector2i(0, 1), sf::Vector2i(11, 1), sf::Vector2i(192, 192));
	this->animationComponent->addAnimation("WALK_RIGHT", 15, sf::Vector2i(0, 1), sf::Vector2i(11, 1), sf::Vector2i(192, 192));
	this->animationComponent->addAnimation("WALK_DOWN", 15, sf::Vector2i(0, 1), sf::Vector2i(11, 1), sf::Vector2i(192, 192));
	this->animationComponent->addAnimation("WALK_UP", 15, sf::Vector2i(0, 1), sf::Vector2i(11, 1), sf::Vector2i(192, 192));
	this->animationComponent->addAnimation("ATTACK", 6, sf::Vector2i(0, 2), sf::Vector2i(13, 2), sf::Vector2i(384, 192));

	if (!this->sprite.getTexture()) { this->sprite.setTexture(*texture_sheet); }
}

Character::~Character()
{

}

void Character::Update(const float& DeltaTime)
{
	if (this->movementComponent)
	{
		this->movementComponent->Update(DeltaTime);
		this->UpdateAnimation(DeltaTime);
	}
	if(this->hitboxComponent)
		this->hitboxComponent->Update(DeltaTime);
}

void Character::AttackAnimation(const float& DeltaTime)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->isAttacking = true;
	}

	if (this->isAttacking) 
	{ 
		if (this->sprite.getScale().x > 0.0f)
		{
			this->sprite.setOrigin(96.0f, 0.0f);
		}
		else
		{
			this->sprite.setOrigin(258.0f + 96.0f, 0.0f);
		}

		this->movementComponent->isEnabled = false; //Disables movement while attacking

		this->animationComponent->Play("ATTACK", DeltaTime, true);

		if (this->animationComponent->isDone("ATTACK"))
		{
			this->isAttacking = false;

			if (this->sprite.getScale().x > 0.0f)
			{
				this->sprite.setOrigin(0.0f, 0.0f);
			}
			else if(this->sprite.getScale().x < 0.0f)
			{
				this->sprite.setOrigin(258.0f, 0.0f);
			}

			this->movementComponent->isEnabled = true; //Enables movement after attacking is done!!
		}
	}
}

void Character::MovementAnimation(const float& DeltaTime)
{
	if (this->movementComponent->getVelocity().x < 0.0f) //Walking LEFT
	{
		if (this->sprite.getScale().x < 0.0f)
		{
			this->sprite.setOrigin(sf::Vector2f(0.0f, 0.0f));
			this->sprite.setScale(sf::Vector2f(1, 1));
		}
		this->animationComponent->Play("WALK_LEFT", DeltaTime,
			this->movementComponent->getVelocity().x, -this->movementSpeed);
	}
	else if (this->movementComponent->getVelocity().x > 0.0f) //Walking RIGHT
	{
		if (this->sprite.getScale().x > 0.0f)
		{
			this->sprite.setOrigin(sf::Vector2f(258.0f, 0.0f));
			this->sprite.setScale(sf::Vector2f(-1, 1));
		}
		this->animationComponent->Play("WALK_RIGHT", DeltaTime,
			this->movementComponent->getVelocity().x, this->movementSpeed);
	}
	else if (this->movementComponent->getVelocity().x == 0.0f)
	{
		if (this->movementComponent->getVelocity().y > 0.0f)  //Walking DOWNWARD
		{
			this->animationComponent->Play("WALK_DOWN", DeltaTime,
				this->movementComponent->getVelocity().y, this->movementSpeed);
		}
		else if (this->movementComponent->getVelocity().y < 0.0f) //Walking UPWARD
		{
			this->animationComponent->Play("WALK_UP", DeltaTime,
				this->movementComponent->getVelocity().y, -this->movementSpeed);
		}
		else if (this->movementComponent->getVelocity().y == 0.0f) //IDLE
			this->animationComponent->Play("IDLE", DeltaTime);
	}
}

void Character::UpdateAnimation(const float& DeltaTime)
{
	this->AttackAnimation(DeltaTime);
	this->MovementAnimation(DeltaTime);
}

//void Character::UpdateInput(std::map<std::string, int> keyBinds, const float& DeltaTime)
//{
//	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keyBinds.at("MOVE_RIGHT")))
//		this->player->move(DeltaTime, 1.0f, 0.0f);
//	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keyBinds.at("MOVE_LEFT")))
//		this->player->move(DeltaTime, -1.0f, 0.0f);
//	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keyBinds.at("MOVE_UP")))
//		this->player->move(DeltaTime, 0.0f, -1.0f);
//	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keyBinds.at("MOVE_DOWN")))
//		this->sprite.move(DeltaTime, 0.0f, 1.0f);
//}
