#pragma once

#include "_CORE.h"
#include "MPE/MPEPCH.h"
// #include "spdlog/spdlog.h"
// #include "spdlog/fmt/ostr.h"

namespace MPE
{
    class MPE_API Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// ENGINE SIDE LOGS
#define MPE_CORE_ERROR(...) ::MPE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MPE_CORE_WARN(...)  ::MPE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MPE_CORE_INFO(...)  ::MPE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MPE_CORE_TRACE(...) ::MPE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MPE_CORE_FATAL(...) ::MPE::Log::GetCoreLogger()->fatal(__VA_ARGS__)
// CLIENT SIDE LOGS
#define MPE_ERROR(...)      ::MPE::Log::GetClientLogger()->error(__VA_ARGS__)
#define MPE_WARN(...)       ::MPE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MPE_INFO(...)       ::MPE::Log::GetClientLogger()->info(__VA_ARGS__)
#define MPE_TRACE(...)      ::MPE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MPE_FATAL(...)      ::MPE::Log::GetClientLogger()->fatal(__VA_ARGS__)