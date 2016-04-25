#include "mywindows.h"

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	
	Window win(hInstance);
	if (win.Create(L"Ave Caesare, Morituri te salutant", 300, 300, 800, 500, WS_TILEDWINDOW))
	{
		win.Show(nCmdShow);
	}
	//win2.Show(nCmdShow);
}
