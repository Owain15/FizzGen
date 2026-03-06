#pragma once

#ifdef FG_PLATFORM_WINDOWS

extern FizzGen::Application* FizzGen::CreateApplication();

int main(int argc, char** argv)
{
	auto app = FizzGen::CreateApplication();
	app->run();
	delete app;

	return 0;
}

#endif // FG_PLATFORM_WINDOWS

