#pragma once

#ifdef MPE_PLATFORM_WINDOWS
#include <Windows.h>
#endif

// BASIC
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <random>

// STRING, STRING MANIPULATION, FILE MANIPULATION
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>

// DATA STRUCTURES
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// MPE
#include "MPE/Base/_CORE.h"
#include "MPE/Base/_TIME.h"
#include "MPE/Base/Log.h"

// ----- PROFILING -----
// ONLY FOR DEBUGGING!
#include "MPE/Debug/Profiling/_TIMER.h"
#include "MPE/Debug/Profiling/_PROFILING.h"
// ----- PROFILING -----