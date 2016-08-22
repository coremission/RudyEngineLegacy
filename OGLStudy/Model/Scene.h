#ifndef MODELS_H
#define MODELS_H

#include <iostream>
#include <map>
#include "GameObject.h"

namespace Models
{
	class Scene
	{
	private:
		std::map<std::string, GameObject*> _gameModelList;
	public:
		Scene();
		~Scene();
		void CreateTriangleModel(const std::string &gameModelName);
		void DeleteModel(const std::string &gameModelName);
		const GameObject& GetModel(const std::string &gameModelName);
		// iterator
		std::map<std::string, GameObject*>::iterator begin();
		std::map<std::string, GameObject*>::iterator end();
	};
}

#endif // MODELS_H