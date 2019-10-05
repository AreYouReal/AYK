#pragma once

#include "Event.h"

namespace AYK {

	class AYK_API KeyEvent : public Event {

	public:
		inline int GetKeyCode() const { return(KeyCode); }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int KeyCodeToSet) : KeyCode(KeyCodeToSet) {}

		int KeyCode;
	};


	class AYK_API KeyPressedEvent : public KeyEvent {

	public:
		KeyPressedEvent(int KeyCode, int RepeatCountToSet) : KeyEvent(KeyCode), RepeatCount(RepeatCountToSet) {}

		inline int GetRepeatCount() const { return (RepeatCount); };

		std::string ToString() const override {
			std::stringstream SS;
			SS << "KeyPressedEvent: " << KeyCode << " (" << RepeatCount << " repeats)";
			return SS.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);

	private:

		int RepeatCount;

	};

	class AYK_API KeyReleaseEvent : public KeyEvent {

	public:
		KeyReleaseEvent(int KeyCodeToSet) : KeyEvent(KeyCodeToSet) {}

		std::string ToString() const override {
			std::stringstream SS;
			SS << "KeyReleaseEvent: " << KeyCode;
			return(SS.str());
		}

		EVENT_CLASS_TYPE(KeyReleased);

	};


	class AYK_API KeyTypedEvent : public KeyEvent {

	public:
		KeyTypedEvent(int KeyCode) : KeyEvent(KeyCode) {}

		std::string ToString() const override {
			std::stringstream SS;
			SS << "KeyTypedEvent: " << KeyCode;
			return SS.str();
		}

		EVENT_CLASS_TYPE(KeyTyped);
	};
}