#pragma once

#include "AYK/Core/Base.h"
#include "Layer.h"

#include <vector>

namespace AYK {

	class LayerStack {
	
	public:

		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* LayerToPush);
		void PushOverlay(Layer* OverlayToPush);
		void PopLayer(Layer* LayerToPop);
		void PopOverlay(Layer* OverlayToPop);

		std::vector<Layer*>::reverse_iterator rbegin() { return(Layers.rbegin()); }
		std::vector<Layer*>::reverse_iterator rend() { return(Layers.rend()); }
		std::vector<Layer*>::iterator begin() { return(Layers.begin()); }
		std::vector<Layer*>::iterator end() { return(Layers.end()); }

		std::vector<Layer*>::const_reverse_iterator rbegin() const { return(Layers.rbegin()); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return(Layers.rend()); }
		std::vector<Layer*>::const_iterator begin() const { return(Layers.begin()); }
		std::vector<Layer*>::const_iterator end() const { return(Layers.end()); }

	private:
		std::vector<Layer*> Layers;
		unsigned int LayerInsertIndex = 0;
	
	};

}


