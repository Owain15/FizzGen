#pragma once

#include "FizzGen/Window.h"

#include <GLFW/glfw3.h>


namespace FizzGen
{
	class WindowsWindow : public Window
	{
		public:
	
			WindowsWindow(const WindowProperties& props);
			virtual ~WindowsWindow();
			
			void OnUpdate() override;
			
			inline unsigned int GetWidth() const override { return m_Data.Width; }
			inline unsigned int GetHeight() const override { return m_Data.Height; }
			void* GetNativeWindow() const override { return m_Window; }

			// Window attributes
			inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; };
			void SetVSync(bool enabled) override;
			bool IsVSync() const override;

		private:
		
			virtual void Init(const WindowProperties& props);
			virtual void Shutdown();

			static void GLFWErrorCallback(int error, const char* description);
	
	private:
			
			GLFWwindow* m_Window;
			struct WindowData
			{
				std::string Title;
				unsigned int Width, Height;
				bool VSync;
				EventCallbackFn EventCallback;
			};
			
			WindowData m_Data;
	
	};
}
