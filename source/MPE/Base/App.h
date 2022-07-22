#pragma once

#include "MPE/Base/Window.h"
#include "MPE/Base/Events/Event.h"
#include "MPE/Base/Layers/LayerStack.h"
#include "MPE/Base/Events/EventApp.h"
#include "MPE/Vendor/ImGui/ImGuiLayer.h"

namespace MPE
{
	class MPE_API App
	{
	private:
		std::unique_ptr<Window> SYS_Window;
		ImGuiLayer *SYS_ImGuiLayer;
		LayerStack SYS_LayerStack;
		static App *SYS_Instance;

		bool SYS_Running = true;
		bool SYS_MINIMIZED = false;

		_TIME SYS_TIME;
		float SYS_LAST_FRAME_TIME = 0.0f;

		bool OnWindowClose(WindowCloseEvent &e);
		bool OnWindowResize(WindowResizeEvent &e);

	public:
		App();
		~App();

		void Run();
		void OnEvent(Event &SYS_Event);

		void PushLayer(Layer *Layer);
		void PushOverlay(Layer *Overlay);

		inline static App &Get() { return *SYS_Instance; }
		inline Window &GetWindow() { return *SYS_Window; }

		inline void Shutdown() { SYS_Running = false; }
	};

	App *CreateApp();
}