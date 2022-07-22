#pragma once

#include <memory>

// COMPILER PREPROCESSOR DIRECTIVES.
// CMAKE BUILD-SET DEFINITIONS:
// CHECKS IF SYSTEM IS ON WIDOWS
#ifdef MPE_PLATFORM_WINDOWS
// IF A STATIC LIBRARY IS USED THEN DEFINE MPE_API AS NOTHING/
#ifdef MPE_STATIC_LIBRARY
#define MPE_API
#endif
// IF A DYNAMIC LIBRARY IS USED THEN DEFINE MPE_API WITHIN MPE AS DLL EXPORT AND MPE_API WITHIN SANDBOX AS DLL IMPORT.
#ifdef MPE_DYNAMIC_LIB
#ifdef MPE_BUILD_DLL
#define MPE_API __declspec(dllexport)
#else
#define MPE_API __declspec(dllimport)
#endif
// DYNAMIC LIBRARY IS NOT SUPPORTED BY THIS PROJECT, BUT CAN STILL BE ENABLED.
#error DYNAMIC LIBRARY IS NOT INTENDED TO BE USED WITH THIS PROJECT.
#endif
#else
#error MPE SUPPORTS ONLY WINDOWS.
#endif

#ifdef MPE_PLATFORM_LINUX
#error MPE SUPPORTS ONLY WINDOWS.
#endif

// CMAKE BUILD-SET DEFINITIONS:
// MPE ASSERTIONS.
#ifdef MPE_ENABLE_ASSERTS
// LOGGING ASSERTIONS FOR DEBUG BUILDS.
#define MPE_ASSERT(x, ...)                                   \
	{                                                        \
		if (!(x))                                            \
		{                                                    \
			MPE_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); \
			__debugbreak();                                  \
		}                                                    \
	}
#define MPE_CORE_ASSERT(x, ...)                                   \
	{                                                             \
		if (!(x))                                                 \
		{                                                         \
			MPE_CORE_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); \
			__debugbreak();                                       \
		}                                                         \
	}
#else
// IF NO CMAKE BUILD-SET DEFINITIONS THEN SET AS NOTHING (FOR RELEASE BUILDS).
#define MPE_ASSERT(x, ...)
#define MPE_CORE_ASSERT(x, ...)
#endif

// HEADER SET DEFINITIONS:

// RIGHT SHIFT OPERATION FOR EVENT ENUMS.
#define BIT(x) (1 << x)

// OPENGL DEFINITIONS:
#define OPENGL_SHADER_TYPE_AMOUNT 2

// BIND FUNCTIONS FOR EVENTS.
#define MPE_BIND_EVENT_FUNCTION(func) std::bind(&func, this, std::placeholders::_1)

namespace MPE
{
	template <typename T>
	using SCOPE = std::unique_ptr<T>;
	template <typename T, typename... Args>
	constexpr SCOPE<T> NEWSCOPE(Args &&...args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using REF = std::shared_ptr<T>;
	template <typename T, typename... Args>
	constexpr REF<T> NEWREF(Args &&...args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}