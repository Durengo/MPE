#include "App.h"
#include "MPE/MPEPCH.h"
#include "Input.h"
#include "MPE/Base/Log.h"

namespace MPE
{
	App *App::SYS_Instance = nullptr;

	App::App()
	{
		MPE_CORE_ASSERT(!SYS_Instance, "APP ALREADY EXISTS.")
		SYS_Instance = this;

		MPE::Log::Init();
		SYS_Window = std::unique_ptr<Window>(Window::Create());
		SYS_Window->SetEventCallback(MPE_BIND_EVENT_FUNCTION(App::OnEvent));

		SYS_ImGuiLayer = new ImGuiLayer();
		PushOverlay(SYS_ImGuiLayer);
	}

	App::~App() {}

	void App::Run()
	{
		while (SYS_Running)
		{
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer *layer : SYS_LayerStack)
			{
				layer->OnUpdate();
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
		}
	}

	void App::OnEvent(Event &SYS_Event)
	{
		EventDispatcher dispatcher(SYS_Event);
		dispatcher.Dispatch<WindowCloseEvent>(MPE_BIND_EVENT_FUNCTION(App::OnWindowClose));
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
		SYS_Running = false;
		return true;
	}
}