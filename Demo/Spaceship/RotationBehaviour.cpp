﻿#include "RotationBehaviour.h"
#include <Dependencies/glm/detail/type_vec3.hpp>
#include <System/Time.h>

RotationBehaviour::RotationBehaviour(GameObject* game_object)
	: Component(game_object)
{
}

void RotationBehaviour::Update()
{
	transform->setLocalYawPitchRoll(
		transform->getLocalYawPitchRoll() + 
		glm::vec3(0.0f, 0.0f, 0.1f * Time::deltaTime)
	);
}