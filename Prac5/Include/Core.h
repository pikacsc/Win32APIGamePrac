#pragma once
#include "Game.h"

class Core
{
private:
	static Core* m_pInstance;
public:
	static Core* GetIntance()
	{
		if (!m_pInstance)
			m_pInstance = new Core;
		return m_pInstance;
	}

	static void DestroyInstance()
	{
		SAFE_DELETE(m_pInstance);
	}

	ATOM MyRegisterClass();
	BOOL Create();

public:
	Core();
	~Core();


private:
	static bool m_bLoop;

private:
	HINSTANCE		m_hInst;
	HWND			m_hWnd;
	RESOLUTION		m_tRS;

public:
	bool	Init(HINSTANCE hInst);

	int Run();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

