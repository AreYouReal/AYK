#pragma once

#ifdef AYK_PLATFORM_WINDOWS
	#ifdef AYK_BUILD_DLL
		#define AYK_API __declspec(dllexport)
	#else
		#define AYK_API __declspec(dllimport)
	#endif
#else
	#error AYK only supports Windows!
#endif

#ifdef AYK_ENABLE_ASSERTS
	#define AYK_ASSERT(x, ...) { if(!(x)){ AYK_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak();}}
	#define AYK_CORE_ASSERT(x, ...){ if(!(x)){ AYK_CORE_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define AYK_ASSERT(x, ...)
	#define AYK_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)