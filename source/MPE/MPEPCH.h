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

// STRING & STRING MANIPULATION
#include <string>
#include <sstream>

// DATA STRUCTURES
#include <vector>
#include <unordered_map>
#include <unordered_set>

// SPDLOG
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

//#include <>
// GRAPHICS
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// IMGUI
#include "imgui.h"
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// MPE
//#include "base/Log.h"