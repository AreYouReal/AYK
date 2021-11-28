#include "aykpch.h"
#include "Scene.h"

#include <glm/glm.hpp>

namespace AYK {



    Scene::Scene() {
        
  //      struct MeshComponent {

  //      };

  //      struct TransformComponent {
  //          glm::mat4 Transform;
  //      
  //          TransformComponent() = default;
  //          TransformComponent(const TransformComponent&) = default;
  //          TransformComponent(const glm::mat4& TMat) : Transform(TMat) {}

  //          operator glm::mat4& () { return(Transform); }
  //          operator const glm::mat4&() const { return(Transform); }
  //      
  //      };
  //      
  //      entt::entity E = ERegistry.create();
  //      ERegistry.emplace<TransformComponent>(E, glm::mat4(1.0f));


  //      auto View = ERegistry.view<TransformComponent>();
  //      for (auto Entity : View) {
  //          
  //          TransformComponent Tr = View.get<TransformComponent>(Entity);
  //      }

  //      auto Group = ERegistry.group<TransformComponent>(entt::get<MeshComponent>);
		//for (auto Entity : Group) {

		//	auto&[Tr, M] = Group.get<TransformComponent, MeshComponent>(Entity);
		//}
    }

    Scene::~Scene() {
        
    }

}