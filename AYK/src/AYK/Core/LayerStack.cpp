#include "aykpch.h"
#include "LayerStack.h"

namespace AYK {

	LayerStack::LayerStack() {	}

	LayerStack::~LayerStack() {
		for (Layer* L : Layers) {
			delete L;
		}
	}

	void LayerStack::PushLayer(Layer* LayerToPush) {
		Layers.emplace( Layers.begin() + LayerInsertIndex, LayerToPush);
		++LayerInsertIndex;
	}

	void LayerStack::PushOverlay(Layer* OverlayToPush) {
		Layers.emplace_back(OverlayToPush);
	}

	void LayerStack::PopLayer(Layer* LayerToPop) {
		auto Iterator = std::find(Layers.begin(), Layers.end(), LayerToPop);
		if (Iterator != Layers.end()) {
			Layers.erase(Iterator);
			--LayerInsertIndex;
		}
	}

	void LayerStack::PopOverlay(Layer* OverlayToPop) {
		auto Iterator = std::find(Layers.begin(), Layers.end(), OverlayToPop);
		if (Iterator != Layers.end()) {
			Layers.erase(Iterator);
		}
	}

}