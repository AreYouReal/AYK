#pragma once

#include "entt.hpp"

namespace AYK {

	class Scene {

	public:
		Scene();
		~Scene();

	private:
		entt::registry ERegistry;
	};


}