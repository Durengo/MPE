#pragma once

#include "MPE/Core/_CORE.h"
#include "spdlog/spdlog.h"

/**
 * @file Log.h
 * @brief Extensible logging system for the engine.
 * @date 2024-05-05
 * @author Sebastian Termen
 */

namespace MPE
{
    class MPE_API Log
    {
    public:
        enum Option
        {
            // 0b00000001
            CONSOLE = 1 << 0,
            // 0b00000010
            FILE = 1 << 1,
        };

        Log(const std::string &name, int options, std::string filename = "");

        // Logging methods
        void trace(const std::string &message);

        void info(const std::string &message);

        void warn(const std::string &message);

        void error(const std::string &message);

        void debug(const std::string &message);

        void critical(const std::string &message);

    private:
        REF<spdlog::logger> logger;
        std::vector<REF<spdlog::sinks::sink>> sinks;
    };
}