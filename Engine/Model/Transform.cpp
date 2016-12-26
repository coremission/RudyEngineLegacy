﻿#include "Transform.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.inl>

using namespace glm;

Transform::Transform():
	localPosition(vec3()),
	localScale(vec3(1, 1, 1)),
	localRotation(vec3()),
	parent(nullptr)
{
}

Transform::~Transform()
{
}

void Transform::recalculateMatrices() const
{
	auto result = translate(localPosition) * scale(localScale) * glm::mat4_cast(localRotation);
	if (parent != nullptr)
		result = parent->localToWorldMatrix * result;

	if (parent != nullptr)
		rotation = parent->getRotation() * localRotation;
	else
		rotation = localRotation;

	localToWorldMatrix = result;
	worldToLocalMatrix = glm::inverse(localToWorldMatrix);
}

void Transform::setLocalPosition(vec3 value)
{
	localPosition = value;
	recalculateMatrices();
}

void Transform::setLocalRotation(glm::quat value)
{
	localRotation = value;
	recalculateMatrices();
}

void Transform::setLocalYawPitchRoll(glm::vec3 yawPitchRoll)
{
	localRotation = quat(yawPitchRoll);
	recalculateMatrices();
}

void Transform::addLocalYawPitchRoll(glm::vec3 yawPitchRoll)
{
	localRotation = localRotation * quat(yawPitchRoll);
	recalculateMatrices();
}

void Transform::LookAt(glm::vec3 worldPosition)
{
	auto thisWorldForward = transformDirection(vec3(0, 0, 1));
	auto lookQuaternion = quat_cast(glm::lookAt(thisWorldForward, worldPosition, vec3(0, 1, 0)));
	setLocalRotation(localRotation * lookQuaternion);
}

void Transform::setLocalScale(glm::vec3 value)
{
	localScale = value;
	recalculateMatrices();
}

const mat4& Transform::getLocalToWorldMatrix() const
{
	recalculateMatrices();
	return localToWorldMatrix;
}

const glm::mat4& Transform::getWorldToLocalMatrix() const
{
	recalculateMatrices();
	return worldToLocalMatrix;
}

glm::vec3 Transform::transformPoint(glm::vec3 p)
{
	return vec3(getLocalToWorldMatrix() * vec4(p, 1.0f));
}

glm::vec3 Transform::inverseTransformPoint(glm::vec3 p)
{
	return vec3(getWorldToLocalMatrix() * vec4(p, 1.0f));
}

glm::vec3 Transform::transformDirection(glm::vec3 direction)
{
	return vec3(getLocalToWorldMatrix() * vec4(direction, 0));
}

glm::vec3 Transform::inverseTransformDirection(glm::vec3 direction)
{
	return vec3(getWorldToLocalMatrix() * vec4(direction, 0));
}