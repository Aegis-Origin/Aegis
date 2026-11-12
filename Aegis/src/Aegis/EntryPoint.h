#pragma once
#ifdef AG_PLATFORM_WINDOWS

extern Aegis::Application* Aegis::CreateApplication();

int main(int argc, char** argv)
{
	Aegis::Log::Init();
	AG_CORE_WARN("Initialized Log!");

	auto app = Aegis::CreateApplication();
	app->Run();
	delete app;
}
#endif // AG_PLATFORM_WINDOWS
