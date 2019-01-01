#pragma once
#include<Windows.h>
//window api variables
HWND			g_hWnd;
HDC				g_hDC;
bool			g_bLoop = true;

//game global_variables
RECT			g_ClientRECT; //client Rectangle
fRECTANGLE      g_tPlayerSquare;

namespace Game
{
	void KeyBoardInteract()
	{
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			g_bLoop = false;
		}
	}


	void Init()
	{
		//initalize client area --
		g_ClientRECT = { 0, 0, 600, 800 };
		AdjustWindowRect(&g_ClientRECT, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(g_hWnd, HWND_TOPMOST, 100, 100,
			g_ClientRECT.right - g_ClientRECT.left,
			g_ClientRECT.bottom - g_ClientRECT.top,
			SWP_NOMOVE | SWP_NOZORDER);
		//-- initalize client area

	}

	void Update()
	{
		KeyBoardInteract();
	}
	
	void Render()
	{
		
	}

	void Release()
	{
		ReleaseDC(g_hWnd, g_hDC);
	}

}
