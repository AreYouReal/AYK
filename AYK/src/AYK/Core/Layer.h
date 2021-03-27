#pragma once

#include "AYK/Core/Base.h"
#include "AYK/Core/Timestep.h"
#include "AYK/Events/Event.h"

namespace AYK {

	class AYK_API Layer {

	public:

		Layer(const std::string& Name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep TimeStep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& E) {}

		inline const std::string& GetName() const { return(DebugName); }

	protected:
		std::string DebugName;
	};

}