#pragma once

#include <memory>

// Platform detected using predefined macros
#ifdef _WIN32
	/* Windows x64/x86*/
	#ifdef _WIN64
		/* Windows x64*/
		#define AYK_PLATFORM_WINDOWS
	#else 
		/* Windows x86*/
		#error "x86 Builds atr not supported"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all platforms
	so we must check all of them (in this order)
	to ensure that we're running on MAC
	and not some other Apple platform
	*/
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_PHONE == 1
		#define AYK_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define AYK_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
	/* We also have to check __ANDROID__ before __linux__
	since android is based on the linux kernel
	it has __linux__ defined */
#elif defined(__ANDROID__)
	#define AYK_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	define AYK_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
#error "Unknown platform!"
#endif // End of platform detection

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
#endif // END of DLL support

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
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}


}