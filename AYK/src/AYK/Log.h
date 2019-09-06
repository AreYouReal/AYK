#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace AYK {
	
	class AYK_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return  s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return  s_ClientLogger; }

	private:

		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}

// Core log macros
#define AYK_CORE_TRACE(...)		::AYK::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AYK_CORE_INFO(...)		::AYK::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AYK_CORE_WARN(...)		::AYK::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AYK_CORE_ERROR(...)		::AYK::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AYK_CORE_FATAL(...)		::AYK::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// CLient log macros
#define AYK_TRACE(...)		::AYK::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AYK_INFO(...)		::AYK::Log::GetClientLogger()->info(__VA_ARGS__)
#define AYK_WARN(...)		::AYK::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AYK_ERROR(...)		::AYK::Log::GetClientLogger()->error(__VA_ARGS__)
#define AYK_FATAL(...)		::AYK::Log::GetClientLogger()->fatal(__VA_ARGS__)


