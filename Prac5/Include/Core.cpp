#include "Core.h"
#include "Scene/SceneManager.h"
#include "Core/Timer.h"

Core* Core::m_pInstance = NULL;
bool  Core::m_bLoop = true;
Core::Core()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(blockNumber);
}


Core::~Core()
{
	DESTROY_SINGLE(SceneManager);
	DESTROY_SINGLE(Timer);
}

ATOM Core::MyRegisterClass()
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Core::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"AR13API";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
	return RegisterClassExW(&wcex);
}

BOOL Core::Create()
{
	m_hWnd = CreateWindowW(L"AR13API", L"AR13API", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);
	if (!m_hWnd)
		return FALSE;


	RECT rc = { 0, 0, static_cast<long>(m_tRS.iW),  static_cast<long>(m_tRS.iH) };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	SetWindowPos(m_hWnd,
		HWND_TOPMOST,
		100,
		100,
		rc.right - rc.left, //808-(-8)  == 816px
		rc.bottom - rc.top, //608-(-31) == 639px
		SWP_NOMOVE | SWP_NOZORDER);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return TRUE;
}


bool Core::Init(HINSTANCE hInst)
{
	m_hInst = hInst;

	MyRegisterClass();

	//set resolution
	m_tRS.iW = 1280;
	m_tRS.iH = 720;

	Create();
	
	//initialize DC
	m_hDC = GetDC(m_hWnd);

	//initialize Timer
	if (!GET_SINGLE(Timer)->Init())
		return false;

	//initialize SceneManager
	if (!GET_SINGLE(SceneManager)->Init())
		return false;

	return true;
}


int Core::Run()
{
	MSG msg;

	//Message Loop
	while (m_bLoop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Logic();
		}
	}
	return (int)msg.wParam;
}

LRESULT Core::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		m_bLoop = false;
		SendMessage(hWnd, WM_CLOSE, NULL, NULL);
		ExitProcess(1);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void Core::Logic()
{
	//renewaling timer
	GET_SINGLE(Timer)->Update();

	float fDeltaTime = GET_SINGLE(Timer)->GetDeltaTime();//initialize common delta Time

	Input(fDeltaTime);
	Update(fDeltaTime);
	LateUpdate(fDeltaTime);
	Collision(fDeltaTime);
	Render(fDeltaTime);
}

void Core::Input(const float & fDeltaTime)
{
	GET_SINGLE(SceneManager)->Input(fDeltaTime);
}

int Core::Update(const float & fDeltaTime)
{
	GET_SINGLE(SceneManager)->Update(fDeltaTime);
	return 0;
}

int Core::LateUpdate(const float & fDeltaTime)
{
	GET_SINGLE(SceneManager)->LateUpdate(fDeltaTime);
	return 0;
}

void Core::Collision(const float & fDeltaTime)
{
	GET_SINGLE(SceneManager)->Collision(fDeltaTime);
}

void Core::Render(const float & fDeltaTime)
{
	GET_SINGLE(SceneManager)->Render(m_hDC, fDeltaTime);
}



