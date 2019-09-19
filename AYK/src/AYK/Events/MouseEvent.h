#pragma once

#include "Event.h"

namespace AYK {

	class AYK_API MouseMovedEvent : public Event {

	public:
		MouseMovedEvent(float XCoord, float YCoord) : X(XCoord), Y(YCoord) {}

		inline float GetX() const { return(X); }
		inline float GetY() const { return(Y); }

		std::string ToString() const override {
			std::stringstream SS;
			SS << "MouseMovedEvent: " << X << ", " << Y;
			return(SS.str());
		}

		EVENT_CLASS_TYPE(MouseMoved);
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

	private:
		float X, Y;

	};


	class AYK_API MouseScrolledEvent : public Event {

	public:
		MouseScrolledEvent(float XOffsetToSet, float YOffsetToSet) : XOffset(XOffsetToSet), YOffset(YOffsetToSet) {}

		inline float GetXOffset() const { return(XOffset); }
		inline float GetYOffset() const { return(YOffset); }

		std::string ToString() const override {
			std::stringstream SS;
			SS << "MouseScrolledEvent: " << XOffset << ", " << YOffset;
			return(SS.str());
		}

		EVENT_CLASS_TYPE(MouseScrolled);
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

	private:
		float XOffset, YOffset;

	};

	class AYK_API MouseButtonEvent : public Event {

	public:
		inline int GetMouseButton() const { return(Button); }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

	protected:
		MouseButtonEvent(int ButtonToSet) : Button(ButtonToSet) {}

		int Button;
	};


	class AYK_API MouseButtonPressedEvent : public MouseButtonEvent {

	public:
		MouseButtonPressedEvent(int ButtonToSet) : MouseButtonEvent(ButtonToSet) {}

		std::string ToString() {
			std::stringstream SS;
			SS << "MouseButtonPressedEvent: " << Button;
			return(SS.str());
		}

		EVENT_CLASS_TYPE(MouseButtonPressed);
	};

	class AYK_API MouseButtonReleasedEvent : public MouseButtonEvent {

	public:
		MouseButtonReleasedEvent(int ButtonToSet) : MouseButtonEvent(ButtonToSet) {}

		std::string ToString() {
			std::stringstream SS;
			SS << "MouseButtonReleasedEvent: " << Button;
			return(SS.str());
		}

		EVENT_CLASS_TYPE(MouseButtonReleased);
	};



}