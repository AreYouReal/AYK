#pragma once

#include <string>
#include <memory>
#include <functional>

#include "AYK/Core/Base.h"

namespace AYK {

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};


#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return(EventType::##type); }\
									virtual EventType GetEventType() const override { return(GetStaticType());}\
									virtual const char* GetName() const override {return(#type);}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return(category);}

	class AYK_API Event {
		friend class EventDispatcher;
	public:
		
		virtual ~Event() = default;
		
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory Category) {
			return(GetCategoryFlags() & Category);
		}
		

		bool bHandled = false;
	};

	class EventDispatcher {

		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& EventToSet) : TheEvent(EventToSet) {}

		template<typename T>
		bool Dispatch(EventFn<T> Function) {
			if (TheEvent.GetEventType() == T::GetStaticType()) {
				TheEvent.bHandled = Function(*(T*)&TheEvent);
				return(true);
			}
			return(false);
		}

	private:
		Event& TheEvent;

	};

	inline std::ostream& operator<<(std::ostream& OS, const Event& E) {
		return(OS << E.ToString());
	}

}