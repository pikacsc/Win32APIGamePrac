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
	HDC				m_hDC;
	RESOLUTION		m_tRS;

public:
	RESOLUTION GetResolution() const
	{
		return m_tRS;
	}

public:
	bool	Init(HINSTANCE hInst);

	int Run();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void Logic();
	void Input(const float& fDeltaTime);
	int Update(const float& fDeltaTime);
	int LateUpdate(const float& fDeltaTime);
	void Collision(const float& fDeltaTime);
	void Render(const float& fDeltaTime);
};

