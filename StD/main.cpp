#include <DxLib.h>
#include "SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	lpSceneManager.Run();

	DxLib_End();
	return 0;
}