#pragma once

#include <memory>

#ifdef AYK_PLATFORM_WINDOWS
#if AYK_DYNAMIC_LINK
	#ifdef AYK_BUILD_DLL
		#define AYK_API __declspec(dllexport)
	#else
		#define AYK_API __declspec(dllimport)
	#endif
#else
	#define AYK_API
#endif
#else
	#error AYK only supports Windows!
#endif

#ifdef AYK_DEBUG
	#define AYK_ENABLE_ASSERTS
#endif

#ifdef AYK_ENABLE_ASSERTS
	#define AYK_ASSERT(x, ...) { if(!(x)){ AYK_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak();}}
	#define AYK_CORE_ASSERT(x, ...){ if(!(x)){ AYK_CORE_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define AYK_ASSERT(x, ...)
	#define AYK_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define AYK_BIND_EVENT_FN(function) std::bind(&function, this, std::placeholders::_1)

namespace AYK {

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Scope = std::unique_ptr<T>;

}