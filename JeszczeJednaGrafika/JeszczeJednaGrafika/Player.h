#pragma once
#include "Entity.h"
class Player :
	public Entity
{
public:
	unsigned int score;
	Player(glm::vec3 position, glm::vec3 centralPoint, char* modelPath) : Entity(position, centralPoint, modelPath) {};
};

