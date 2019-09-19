#pragma once

#include "Event.h"

namespace AYK {

	class AYK_API WindowResizeEvent : public Event {
		
	public:
		WindowResizeEvent(unsigned int NewWidth, unsigned int NewHeight) : Width(NewWidth), Height(NewHeight) {}

		inline unsigned int GetWidth() const { return(Width); }
		inline unsigned int GetHeight() const { return(Height); }

		std::string ToString() const override {
			std::stringstream SS;
			SS << "WindowResizeEvent: " << Width << ", " << Height;
			return(SS.str());
		}


		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:

		unsigned int Width, Height;

	};

	class AYK_API WindowCloseEvent : public Event {

	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};


	class AYK_API AppTickEvent : public Event {

	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

	class AYK_API AppUpdateEvent : public Event {

	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

	class AYK_API AppRenderEvent : public Event {

	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

}