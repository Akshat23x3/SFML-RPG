#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet) : 
	sprite(sprite), texture_sheet(texture_sheet), lastAnimated(nullptr), priorityAnimation(nullptr)
{

}

AnimationComponent::~AnimationComponent()
{ 
	for (auto& itr : this->animations)
		delete itr.second;

	delete lastAnimated;
}

void AnimationComponent::Play(const std::string key, const float& DeltaTime, 
const bool priority)
{
	if (this->animations.empty()) { return; }

	if (priority) { this->priorityAnimation = this->animations[key]; }

	if (this->priorityAnimation)
	{
		if (this->animations[key] == this->priorityAnimation)
		{
			if (lastAnimated != this->animations[key])
			{
				if (lastAnimated != nullptr)
					lastAnimated->Reset();
				lastAnimated = this->animations[key];
			}

			//If the Priority animation is done remove it
			if (this->animations[key]->Play(DeltaTime))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else
	{
		if (lastAnimated != this->animations[key])
		{
			if (lastAnimated != nullptr)
				lastAnimated->Reset();
			lastAnimated = this->animations[key];
		}

		this->animations[key]->Play(DeltaTime);
	}
	
}


void AnimationComponent::Play(const std::string key, const float& DeltaTime,
	float modifier,
	float modifier_max, const bool priority)
{
	if (this->animations.empty()) { return; }

	if (priority) { this->priorityAnimation = this->animations[key]; }

	if (this->priorityAnimation)
	{
		if (this->animations[key] == this->priorityAnimation)
		{
			if (lastAnimated != this->animations[key])
			{
				if (lastAnimated != nullptr)
					lastAnimated->Reset();
				lastAnimated = this->animations[key];
			}

			//If the Priority animation is done remove it
			if(this->animations[key]->Play(DeltaTime, abs(modifier / modifier_max)))
				this->priorityAnimation = NULL;
		}
		
	}
	else
	{
		if (lastAnimated != this->animations[key])
		{
			if (lastAnimated != nullptr)
				lastAnimated->Reset();
			lastAnimated = this->animations[key];
		}

		this->animations[key]->Play(DeltaTime, abs(modifier / modifier_max));
	}
}

void AnimationComponent::addAnimation(const std::string key,
	float animationTimer,
	sf::Vector2i startFrameIndex, sf::Vector2i endFrameIndex,
	sf::Vector2i Dimensions)
{
	this->animations[key] = new Animation(
		this->sprite,
		this->texture_sheet,
		animationTimer,
		startFrameIndex, endFrameIndex,
		Dimensions);
}





