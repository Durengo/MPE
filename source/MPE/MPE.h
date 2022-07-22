#pragma once

// For external apps

// ----- APPLICATION -----
#include "MPE/Base/App.h"
#include "MPE/Base/Layers/Layer.h"
#include "MPE/Base/Log.h"
// ----- APPLICATION -----

// ----- PHYSICS -----
#include "MPE/Base/_TIME.h"
// ----- PHYSICS -----

// ----- EVENTS -----
#include "MPE/Base/Events/EventApp.h"
#include "MPE/Base/Events/EventKey.h"
#include "MPE/Base/Events/EventMouse.h"
// ----- EVENTS -----

// ----- INPUT -----
#include "MPE/Base/Input/Input.h"
#include "MPE/Base/Input/KeyCodes.h"
#include "MPE/Base/Input/MouseButtonCodes.h"
// ----- INPUT -----

// ----- IMGUI -----
#include "MPE/Vendor/ImGui/ImGuiLayer.h"
// ----- IMGUI -----

// ----- RENDERER -----
#include "MPE/Renderer/Renderer.h"
#include "MPE/Renderer/RenderPrimitive.h"
// ----- RENDERER -----

// ----- GRAPHICS -----
#include "MPE/Renderer/Pipeline/VertexBuffer.h"
#include "MPE/Renderer/Pipeline/IndexBuffer.h"
#include "MPE/Renderer/Pipeline/VertexArray.h"
#include "MPE/Renderer/Shaders/Shader.h"
#include "MPE/Renderer/Textures/Texture.h"
#include "MPE/Renderer/Textures/Texture2D.h"
// ----- GRAPHICS -----

// ----- CAMERAS -----
#include "MPE/Renderer/Cameras/OrthographicCamera.h"
#include "MPE/Renderer/Cameras/OrthographicCameraController.h"
// ----- CAMERAS -----

//-----Entry Point----
#include "MPE/Base/EntryPoint.h"
//-----Entry Point----