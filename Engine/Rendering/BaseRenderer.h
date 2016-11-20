﻿#ifndef BASERENDERER_h
#define BASERENDERER_h
#include <Model/GameObject.h>
#include "ShaderProgram.h"
#include "Mesh.h"

#include <memory>
#include "rendering.hpp"

class GameObject;

class BaseRenderer: public IRenderer
{
protected:
	const GameObject* const _gameObject;

public:
	std::shared_ptr<LegacyMesh> mesh;
	std::shared_ptr<ShaderProgram> material;
	
	BaseRenderer(GameObject* gameObject, std::shared_ptr<ShaderProgram>, std::shared_ptr<LegacyMesh> mesh);
	virtual ~BaseRenderer();
	virtual void render() const override;

	static std::unique_ptr<BaseRenderer> create(GameObject* gameObject, std::shared_ptr<ShaderProgram> material, std::shared_ptr<LegacyMesh> mesh);
};

#endif // BASERENDERER_h
