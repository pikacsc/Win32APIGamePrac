#pragma once
#include <Windows.h>
#include "constants.h"
using namespace constants;


//window api variables
HWND			g_hWnd;
HDC				g_hDC;
bool			g_bLoop = true;

//game global_variables
RECT			g_ClientRECT; //client Rectangle
fRECTANGLE      g_tPlayerSquare = {};
float			g_fPlayerSpeed;
float			g_fEnemySpeed;

//Delta time
LARGE_INTEGER	g_tSecond;
LARGE_INTEGER	g_tTime;
float			g_fDeltaTime;
float			g_fTimeScale = 1.f;



inline void DrawingRECT(fRECTANGLE _fRECT) {
	Rectangle(g_hDC,static_cast<int>(_fRECT.left),static_cast<int>(_fRECT.top),static_cast<int>(_fRECT.right),static_cast<int>(_fRECT.bottom));
}

inline bool LeftInput() {
	GetClientRect(g_hWnd, &g_ClientRECT); //GetClientRect(hWnd, &clientRECT) - current time window left, top, right, bottom
	return (GetAsyncKeyState(VK_LEFT) & 0x8000) && (g_tPlayerSquare.left > g_ClientRECT.left);
}
inline bool RightInput() {
	GetClientRect(g_hWnd, &g_ClientRECT);
	return (GetAsyncKeyState(VK_RIGHT) & 0x8000) && (g_tPlayerSquare.right < g_ClientRECT.right);
}
inline bool UpInput() {
	GetClientRect(g_hWnd, &g_ClientRECT);
	return (GetAsyncKeyState(VK_UP) & 0x8000) && (g_tPlayerSquare.top > g_ClientRECT.top);
}
inline bool DownInput() {
	GetClientRect(g_hWnd, &g_ClientRECT);
	return (GetAsyncKeyState(VK_DOWN) & 0x8000) && (g_tPlayerSquare.bottom < g_ClientRECT.bottom);
}
inline void UpdatePlayerSpeed() { g_fPlayerSpeed = (iPlayerDefaultSpeed * g_fDeltaTime) * g_fTimeScale;}


namespace Game
{
	void KeyBoardInteract();
	void InitDeltaTime();

	// Initialize Game variables, Game Objects
	void Init()
	{
		QueryPerformanceFrequency(&g_tSecond);
		QueryPerformanceCounter(&g_tTime);
		// client area --
		g_ClientRECT = { ClientRECT_LEFT, ClientRECT_TOP, ClientRECT_RIGHT, ClientRECT_BOTTOM };
		AdjustWindowRect(&g_ClientRECT, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(g_hWnd, HWND_TOPMOST, 100, 100,
			g_ClientRECT.right - g_ClientRECT.left,
			g_ClientRECT.bottom - g_ClientRECT.top,
			SWP_NOMOVE | SWP_NOZORDER);
		//-- client area


		//Player start point
		g_tPlayerSquare = { PlayerStartPoint_LEFT, PlayerStartPoint_TOP ,PlayerStartPoint_RIGHT, PlayerStartPoint_BOTTOM };
		

	}

	void Update()
	{
		InitDeltaTime();
		UpdatePlayerSpeed();
		KeyBoardInteract();
	}
	
	void Render()
	{
		DrawingRECT(g_tPlayerSquare);
	}

	void Release()
	{
		ReleaseDC(g_hWnd, g_hDC);
	}



	void KeyBoardInteract()
	{
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			g_bLoop = false;
		}
		if (LeftInput()) {
			g_tPlayerSquare.left -= g_fPlayerSpeed;
			g_tPlayerSquare.right -= g_fPlayerSpeed;
		}
		if (RightInput()) {
			g_tPlayerSquare.left += g_fPlayerSpeed;
			g_tPlayerSquare.right += g_fPlayerSpeed;
		}
		if (UpInput()) {
			g_tPlayerSquare.top -= g_fPlayerSpeed;
			g_tPlayerSquare.bottom -= g_fPlayerSpeed;
		}
		if (DownInput()) {
			g_tPlayerSquare.top += g_fPlayerSpeed;
			g_tPlayerSquare.bottom += g_fPlayerSpeed;
		}
		if (GetAsyncKeyState(VK_F3) & 0x8000) {
			g_fTimeScale -= g_fDeltaTime;
			if (g_fTimeScale < 0.f)
				g_fTimeScale = 0.f;
		}
		if (GetAsyncKeyState(VK_F4) & 0x8000) {
			g_fTimeScale += g_fDeltaTime;
			if (g_fTimeScale > 1.f)
				g_fTimeScale = 1.f;
		}
	}

	//Initialize Delta time
	void InitDeltaTime()
	{
		LARGE_INTEGER tTime;
		QueryPerformanceCounter(&tTime);
		g_fDeltaTime = (tTime.QuadPart - g_tTime.QuadPart) / static_cast<float>(g_tSecond.QuadPart);
		g_tTime = tTime;

	}
	

}
