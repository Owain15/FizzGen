#pragma once

//Precompiled header for FizzGen

//Standard library headers

#include <iostream>
#include <sstream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

//Data structures

#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "FizzGen/Core/Log.h"
#include "FizzGen/Diagnostics/Instrumentor.h"


//Platform detection

#ifdef FG_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // FG_PLATFORM_WINDOWS


