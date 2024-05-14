#pragma once

#include "MPE/Core/_CORE.h"

#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include <bitset>

#ifdef MPE_PLATFORM_WINDOWS
#include <Windows.h>
#endif

namespace MPE
{
    // Error severity levels
    enum class MPE_API Severity
    {
        Info,
        Warning,
        Error,
        Fatal
    };

    // Error categories using bit flags
    enum class MPE_API Category : uint64_t
    {
        None = 0,
        Global = 1 << 0,
        SystemInternal = 2 << 0,
    };

    MPE_API inline Category operator|(Category a, Category b)
    {
        return static_cast<Category>(static_cast<int>(a) | static_cast<int>(b));
    }

    // Base Error class
    class MPE_API Error : public std::exception
    {
    public:
        Error();
        Error(int code, const std::string &message, Severity severity, Category category);

        virtual void std_log() const;

        virtual std::string get_verbose_log() const;

        virtual const char *what() const noexcept override;

        static const Error &get(int code);

        void showExceptionDialog(const std::exception &e)
        {
#ifdef MPE_PLATFORM_WINDOWS
            std::string errorMessage = "An unhandled exception occurred: ";
            errorMessage += e.what();
            MessageBoxA(NULL, errorMessage.c_str(), "Unhandled Exception", MB_ICONERROR | MB_OK);
#endif
        }

    protected:
        int code_;
        std::string message_;
        Severity severity_;
        Category category_;
    };
}

// Error throwing macro
#define MPE_THROW_ERROR(code) throw MPE::Error::get(code);