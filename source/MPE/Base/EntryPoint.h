#pragma once

#ifdef MPE_PLATFORM_WINDOWS

extern MPE::App *MPE::CreateApp();

int main(int argc, char **argv)
{
	auto app = MPE::CreateApp();
	app->Run();
	delete app;
}

#endif