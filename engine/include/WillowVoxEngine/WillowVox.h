#pragma once

// For use by WillowVox Engine applications

// Application
#include <WillowVoxEngine/Version.h>
#include <WillowVoxEngine/Application/Application.h>
#include <WillowVoxEngine/Application/Window.h>
// Core
#include <WillowVoxEngine/Core/Logger.h>
// Events
#include <WillowVoxEngine/Events/Event.h>
#include <WillowVoxEngine/Events/EventDispatcher.h>
#include <WillowVoxEngine/Events/WindowCloseEvent.h>
#include <WillowVoxEngine/Events/WindowResizeEvent.h>
// Input
#include <WillowVoxEngine/Input/Input.h>
// Rendering
#include <WillowVoxEngine/Rendering/Camera.h>
#include <WillowVoxEngine/Rendering/Mesh.h>
#include <WillowVoxEngine/Rendering/MeshRenderer.h>
#include <WillowVoxEngine/Rendering/OpenGLGraphicsAPI.h>
#include <WillowVoxEngine/Rendering/Shader.h>
#include <WillowVoxEngine/Rendering/Texture.h>
#include <WillowVoxEngine/Rendering/Vertex.h>
// Math (TODO: Don't expose any external libraries to client applications)
#include <glm/glm.hpp>

// --- Entry Point --- //
#include <WillowVoxEngine/Application/EntryPoint.h>
// ------------------- //