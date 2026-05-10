#pragma once



#ifdef FG_PLATFORM_WINDOWS

extern FizzGen::Application* FizzGen::CreateApplication();

int main(int argc, char** argv)
{
	std::string fileName = "diagnostic-data";
	std::string appName = std::filesystem::path(argv[0]).stem().string();


	FizzGen::Log::Init();
	FG_INFO("Welcome to FizzGen!");
	FG_CORE_INFO("log initialized...");
	

	FG_PROFILE_BEGIN_SESSION("StartUp", fileName + "/" + appName + "-Profile-StartUp.json");
	auto app = FizzGen::CreateApplication();
	FG_PROFILE_END_SESSION();

	FG_PROFILE_BEGIN_SESSION("Runtime", fileName + "/" + appName + "-Profile-Runtime.json");
	app->Run();
	FG_PROFILE_END_SESSION();

	FG_PROFILE_BEGIN_SESSION("ShutDown", fileName + "/" + appName + "-Profile-ShutDown.json");
	delete app;
	FG_PROFILE_END_SESSION();

	return 0;
}

#endif // FG_PLATFORM_WINDOWS

