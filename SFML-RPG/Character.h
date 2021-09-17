#pragma once
#include "Entity.h"
class Character :
    public Entity
{
private:
    //Variables
    bool isAttacking;

    //Initializers
    void initVariables();
public:
    Character(float posX, float posY, sf::Texture* texture_sheet, sf::RenderWindow* window);
    ~Character();

    //Functions
    void Update(const float& DeltaTime); 
    void UpdateInput(std::map<std::string, int> keyBinds, const float& DeltaTime);
    void UpdateAnimation(const float& DeltaTime);
    void AttackAnimation(const float& DeltaTime);
    void MovementAnimation(const float& DeltaTime);
};

