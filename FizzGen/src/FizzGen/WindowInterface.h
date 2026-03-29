#pragma once

#include "fgpch.h"

#include "Core.h"
#include "Events/Event.h"

namespace FizzGen
{
	struct WindowProperties
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(const std::string& title = "FizzGen Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height) {
		}

	};

	// Interface representing a desktop system based Window
	class FIZZGEN_API WindowInterface
	{
		public:
			
			using EventCallbackFn = std::function<void(Event&)>;

			virtual ~WindowInterface() {}

			virtual void OnUpdate() = 0;

			virtual unsigned int GetWidth() const = 0;
			virtual unsigned int GetHeight() const = 0;

			// Window attributes
			
			virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
			virtual void SetVSync(bool enabled) = 0;
			virtual bool IsVSync() const = 0;

			virtual void* GetNativeWindow() const = 0;

			static WindowInterface* Create(const WindowProperties& props = WindowProperties());

	};

}

