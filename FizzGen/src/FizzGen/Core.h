#pragma once

// Platform / export macro handling
#ifdef FG_PLATFORM_WINDOWS
    // Project preprocessor definitions use different names for exporting the DLL
    // (e.g. FG_BUILD_DLL_DEBUG, FG_BUILD_DLLNDEBUG). Treat any of them as the
    // intent to export symbols when building the DLL.
    #if defined(FG_BUILD_DLL) || defined(FG_BUILD_DLL_DEBUG) || defined(FG_BUILD_DLLNDEBUG)
        #define FIZZGEN_API __declspec(dllexport)
    #else
        #define FIZZGEN_API __declspec(dllimport)
    #endif // FG_BUILD_DLL
#else
    #error FizzGen Build Not Supported!

#endif // FG_PLATFORM_WINDOWS


