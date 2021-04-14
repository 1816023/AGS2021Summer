#include <DxLib.h>

int WINAPI WinMain(HINSTANCE h, HINSTANCE hi, LPSTR lp, int cmd)
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