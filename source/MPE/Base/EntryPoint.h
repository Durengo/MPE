#pragma once

#ifdef MPE_PLATFORM_WINDOWS

extern MPE::App *MPE::CreateApp();

int main(int argc, char **argv)
{
	MPE_PROFILE_START("STARTUP", "MPE-PROFILE-STARTUP.json");
	auto app = MPE::CreateApp();
	MPE_PROFILE_END();
	MPE_PROFILE_START("RUNTIME", "MPE-PROFILE-RUNTIME.json");
	app->Run();
	MPE_PROFILE_END();
	delete app;
}

#endif