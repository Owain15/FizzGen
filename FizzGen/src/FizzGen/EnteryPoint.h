#pragma once



#ifdef FG_PLATFORM_WINDOWS

extern FizzGen::Application* FizzGen::CreateApplication();

int main(int argc, char** argv)
{

	FizzGen::Log::Init();
	FG_CORE_CRITICAL("Initialized Log!");
	FG_INFO("Welcome to FizzGen!");

	auto app = FizzGen::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif // FG_PLATFORM_WINDOWS

