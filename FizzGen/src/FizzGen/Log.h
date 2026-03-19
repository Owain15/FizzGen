#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace FizzGen
{

	class FIZZGEN_API Log
	{
		public:
			
			static void Init();

			inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
			inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;


	};

}

//Core log macros
#define FG_CORE_TRACE(...)		::FizzGen::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FG_CORE_INFO(...)		::FizzGen::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FG_CORE_WARN(...)		::FizzGen::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FG_CORE_ERROR(...)		::FizzGen::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FG_CORE_CRITICAL(...)	    ::FizzGen::Log::GetCoreLogger()->critical(__VA_ARGS__)


//Client log macros
#define FG_TRACE(...)		::FizzGen::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FG_INFO(...)		::FizzGen::Log::GetClientLogger()->info(__VA_ARGS__)
#define FG_WARN(...)		::FizzGen::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FG_ERROR(...)		::FizzGen::Log::GetClientLogger()->error(__VA_ARGS__)
#define FG_CRITICAL(...)	    ::FizzGen::Log::GetClientLogger()->critical(__VA_ARGS__)

