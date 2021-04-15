#include "Application.h"
#include <assert.h>

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	auto& app = Application::Instance();
	
	if (!app.Init())
	{
		assert(false);
		return -1;
	}
	app.Run();
	app.Terminate();
	return 0;
}