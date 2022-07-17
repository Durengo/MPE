#pragma once

#include "_CORE.h"
#include "Window.h"
#include "MPE/events/Event.h"
#include "MPE/events/EventApp.h"
#include "LayerStack.h"
#include "MPE/imgui/ImGuiLayer.h"

namespace MPE
{
	class MPE_API App
	{
	private:
		std::unique_ptr<Window> SYS_Window;
		ImGuiLayer *SYS_ImGuiLayer;
		bool SYS_Running = true;
		LayerStack SYS_LayerStack;
		bool OnWindowClose(WindowCloseEvent &e);
		static App *SYS_Instance;

	public:
		App();
		~App();
		void Run();
		void OnEvent(Event &SYS_Event);

		void PushLayer(Layer *Layer);
		void PushOverlay(Layer *Overlay);

		inline static App &Get() { return *SYS_Instance; }
		inline Window &GetWindow() { return *SYS_Window; }
	};

	App *CreateApp();
}