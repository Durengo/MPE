#include "MPE/MPEPCH.h"
#include "App.h"
#include "MPE/Base/Input/Input.h"
#include "MPE/Renderer/Renderer.h"

// TEMP
#include <GLFW/glfw3.h>

// TODO: CHECK WHICH MATH LIBRARY TO USE: GLM VS EIGEN VS ARMADILLO
namespace MPE
{
	App *App::SYS_Instance = nullptr;

	App::App()
	{
		MPE_PROFILE_FUNCTION();

		MPE_CORE_ASSERT(!SYS_Instance, "APP ALREADY EXISTS.")
		SYS_Instance = this;

		MPE::Log::Init();
		SYS_Window = std::unique_ptr<Window>(Window::Create());
		SYS_Window->SetEventCallback(MPE_BIND_EVENT_FUNCTION(App::OnEvent));

		Renderer::Init();

		SYS_ImGuiLayer = new ImGuiLayer();
		PushOverlay(SYS_ImGuiLayer);
	}

	App::~App() {}

	void App::Run()
	{
		while (SYS_Running)
		{
			// Platform::GetTime()
			float time = (float)glfwGetTime();
			_TIME deltatime = time - SYS_LAST_FRAME_TIME;
			SYS_LAST_FRAME_TIME = time;

			if (!SYS_MINIMIZED)
			{
				for (Layer *layer : SYS_LayerStack)
				{
					layer->OnUpdate(deltatime);
				}
			}

			SYS_ImGuiLayer->Begin();
			for (Layer *layer : SYS_LayerStack)
			{
				layer->OnImGuiRender();
			}
			SYS_ImGuiLayer->End();

			// EVENT POLLING
			// auto[x, y] = Input::GetMousePosition();
			// MPE_CORE_ERROR("{0}, {1}", x, y);

			SYS_Window->OnUpdate();

			if (Input::IsKeyPressed(MPE_KEY_ESCAPE))
			{
				SYS_Running = false;
			}
		}
	}

	void App::OnEvent(Event &SYS_Event)
	{
		EventDispatcher dispatcher(SYS_Event);
		dispatcher.Dispatch<WindowCloseEvent>(MPE_BIND_EVENT_FUNCTION(App::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(MPE_BIND_EVENT_FUNCTION(App::OnWindowResize));

		for (auto it = SYS_LayerStack.end(); it != SYS_LayerStack.begin();)
		{
			(*--it)->OnEvent(SYS_Event);
			if (SYS_Event.SYS_Handled)
			{
				break;
			}
		}
	}

	void App::PushLayer(Layer *Layer)
	{
		SYS_LayerStack.PushLayer(Layer);
		Layer->OnAttach();
	}

	void App::PushOverlay(Layer *Overlay)
	{
		SYS_LayerStack.PushOverlay(Overlay);
		Overlay->OnAttach();
	}

	bool App::OnWindowClose(WindowCloseEvent &e)
	{
		Shutdown();
		return true;
	}

	bool App::OnWindowResize(WindowResizeEvent &e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			SYS_MINIMIZED = true;
			return false;
		}
		SYS_MINIMIZED = false;

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}