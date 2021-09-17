#pragma once

#include "AudioComponent.h"

class AnimationComponent
{
private:
	class Animation
	{
	public:
		bool done;

		float animationTimer;
		float timer;

		int width;
		int height;

		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		sf::IntRect startRect, endRect, currentRect;

		const bool& Play(const float& DeltaTime, bool priority = false)
		{
			//UpdateTimer
			this->done = false;
			this->timer += 100.0f * DeltaTime;
			if (this->timer >= animationTimer)
			{
				//Reset Timer
				this->timer = 0.0f;

				//Animate
				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->width;
				}
				else //Reset
				{
					this->currentRect.left = this->startRect.left;
					done = true;
				}

				this->sprite.setTextureRect(this->currentRect);
			}

			return done;
		}
		
		const bool& Play(const float& DeltaTime, float speed_percent, bool priority = false)
		{
			//UpdateTimer
			this->done = false;
			if (speed_percent < 0.5f)
				speed_percent = 0.5f;

			this->timer += speed_percent * 100.0f * DeltaTime;
			if (this->timer >= animationTimer)
			{
				//Reset Timer
				this->timer = 0.0f;

				//Animate
				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->width;
				}
				else //Reset
				{
					this->currentRect.left = this->startRect.left;
					done = true;
				}

				this->sprite.setTextureRect(this->currentRect);
			}
			return done;
		}

		void Reset()
		{
			this->timer = 0.0f;
			this->currentRect = this->startRect;
		 
		}

		const bool& isDone() { return this->done; }

		Animation(
			sf::Sprite& sprite,
			sf::Texture& textureSheet,
			float animationTimer,
			sf::Vector2i startFrameIndex, sf::Vector2i endFrameIndex,
			sf::Vector2i Dimensions,
			bool priority = false)
			: sprite(sprite), textureSheet(textureSheet), animationTimer(animationTimer)
		{
			//this->animationTimer = 0.0f;
			this->timer = 0.0f;
			this->done = false;
			this->width = Dimensions.x;
			this->height = Dimensions.y; 
			this->startRect = sf::IntRect(startFrameIndex.x * this->width, startFrameIndex.y * this->height, this->width, this->height);
			this->endRect = sf::IntRect(endFrameIndex.x * this->width, endFrameIndex.y * this->height, this->width, this->height);
			this->currentRect = this->startRect;

			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
		}

		~Animation()
		{
		}
	};

	sf::Sprite& sprite;
	sf::Texture& texture_sheet;

	std::map<std::string, Animation*> animations;

	Animation* lastAnimated;
	Animation* priorityAnimation;

public:

	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);

	~AnimationComponent();

	const bool& isDone(const std::string key) { return this->animations[key]->isDone(); }

	void Play(const std::string key, const float& DeltaTime, const bool priority = false);
	void Play(const std::string key, const float& DeltaTime, float modifier, 
		float modifier_max, const bool priority = false);
	
	void addAnimation(const std::string key,
		float animationTimer,
		sf::Vector2i startFrameIndex, sf::Vector2i endFrameIndex,
		sf::Vector2i Dimensions);
};

