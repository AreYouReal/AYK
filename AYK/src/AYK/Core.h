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