#include <DxLib.h>

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{

	ChangeWindowMode(true);
	SetMainWindowText(L"DC&IC");
	SetGraphMode(1024, 640, 16);
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ProcessMessage() == 0)
	{
		
	}
	DxLib_End();
	return 0;
}