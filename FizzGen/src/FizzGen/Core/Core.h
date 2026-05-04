#pragma once

#include <memory>

// Platform / export macro handling
#ifdef FG_PLATFORM_WINDOWS
   
    #if FG_DYNAMIC_LINK

        // Project preprocessor definitions use different names for exporting the DLL
        // (e.g. FG_BUILD_DLL_DEBUG, FG_BUILD_DLLNDEBUG). Treat any of them as the
        // intent to export symbols when building the DLL.
    
        #if defined(FG_BUILD_DLL) || defined(FG_BUILD_DLL_DEBUG) || defined(FG_BUILD_DLLNDEBUG)
            #define FIZZGEN_API __declspec(dllexport)
        #else
            #define FIZZGEN_API __declspec(dllimport)
        #endif // FG_BUILD_DLL
    #else
        #define FIZZGEN_API
    #endif // FG_DYNAMIC_LINK

#else
    #error FizzGen Build Not Supported!

#endif // FG_PLATFORM_WINDOWS


#ifdef FG_ENABLE_ASSERTS
    #define FG_ASSERT(x, ...) { if(!(x)) { FG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define FG_CORE_ASSERT(x, ...) { if(!(x)) { FG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define FG_ASSERT(x, ...)
    #define FG_CORE_ASSERT(x, ...)
#endif // FG_ENABLE_ASSERTS


#define BIT(x) (1 << x)

#define FG_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace FizzGen
{

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;

}



