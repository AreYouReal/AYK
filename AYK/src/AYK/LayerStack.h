#pragma once

#include "AYK/Core.h"
#include "Layer.h"

#include <vector>

namespace AYK {

	class LayerStack {
	
	public:

		LayerStack();
		~LayerStack();

		void PushLayer(Layer* LayerToPush);
		void PushOverlay(Layer* OverlayToPush);
		void PopLayer(Layer* LayerToPop);
		void PopOverlay(Layer* OverlayToPop);

		std::vector<Layer*>::iterator begin() { return(Layers.begin()); }
		std::vector<Layer*>::iterator end() { return(Layers.end()); }

	private:
		std::vector<Layer*> Layers;
		unsigned int LayerInsertIndex = 0;
	
	};

}


