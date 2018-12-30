#include "stdafx.h"
#include "Prac3.h"
#include <list>
#define MAX_LOADSTRING 100

using namespace std;

//custom RECT, float type elements
typedef struct _tagRectangle
{
	float	left, top, right, bottom;
} fRECTANGLE, *PRECTANGLE;


HINSTANCE			hInst;                               
WCHAR				szTitle[MAX_LOADSTRING];                 
WCHAR				szWindowClass[MAX_LOADSTRING];           
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND				g_hWnd; //initialize global window handle variable
bool				g_bLoop = true; // To use g_bLoop instead "GetMessage(&msg, nullptr, 0, 0)" in Message loop
HDC					g_hDC;
fRECTANGLE			g_tPlayerSquare = {100,100,200,200}; //Player, SquareShape
RECT				g_ClientRECT; //client rectangle
list<fRECTANGLE>	g_PlayerBulletList; //player bullet


//time variables
LARGE_INTEGER		g_tSecond; 
LARGE_INTEGER		g_tTime;
float				g_fDeltaTime;
float				g_fPlayerSpeed;
float				g_fTimeScale = 1.f;

void Run(); // Game Running function
void KeyboardInteract(); // Keyboard input interact, W, A, S, D ...
void InitDeltaTime(); // initialize g_fDeltaTime, g_tTime, 
void Rendering(); //rendering objects on client area, Player, bullets, enemy ...

inline bool LeftInput  (char left )  {
	GetClientRect(g_hWnd, &g_ClientRECT); //GetClientRect(hWnd, &clientRECT) - current time window left, top, right, bottom
	return (GetAsyncKeyState(left)  & 0x8000) && (g_tPlayerSquare.left  > g_ClientRECT.left);
}
inline bool RightInput (char right)  { 
	GetClientRect(g_hWnd, &g_ClientRECT);
	return (GetAsyncKeyState(right) & 0x8000) && (g_tPlayerSquare.right  < g_ClientRECT.right);
}
inline bool UpInput	   (char Up   )  { 
	GetClientRect(g_hWnd, &g_ClientRECT);
	return (GetAsyncKeyState(Up)    & 0x8000) && (g_tPlayerSquare.top    > g_ClientRECT.top);
}
inline bool DownInput  (char Down )  { 
	GetClientRect(g_hWnd, &g_ClientRECT);
	return (GetAsyncKeyState(Down)  & 0x8000) && (g_tPlayerSquare.bottom < g_ClientRECT.bottom);
}



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PRAC3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRAC3));

    MSG msg;

	g_hDC = GetDC(g_hWnd); // initialize window DC, Warning, to avoid memory leak, you must "ReleaseDC(g_hWnd,g_hDC)" at the end.



	//begin -- get time
	QueryPerformanceFrequency(&g_tSecond); // High Performance Timer Function
	QueryPerformanceCounter(&g_tTime);
	//end	-- get time


	//Message Loop
    while (g_bLoop)
    {
		//GetMessage()  - Waiting until next message called, so even animation wouldn't work until next message come.
		
		//PeekMessage() - Not waiting but return false when there is "no message in MessageQueue"(idle Time or dead time), and do another task


        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) //Use PeekMessage(&msg, nullptr, 0, 0) intead TranslateAccelerator(msg.hwnd, hAccelTable, &msg)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		else // idle time(dead time)
		{
			Run(); //Game Running while idle time
		}
    }
	ReleaseDC(g_hWnd, g_hDC); //delete DC

    return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRAC3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL; //no menu 
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;
  
   //begin -- initialize client area --
   g_ClientRECT = { 0, 0, 800, 600 };
   AdjustWindowRect(&g_ClientRECT, WS_OVERLAPPEDWINDOW, FALSE);// Get size of window screen including title bar and men;

   /*SetWindowPos(hWnd,
				  hWndInsertAfter, //HWND_TOPMOST - always most top(front) z position(HWND_TOPMOST > HWND_TOP)
									 HWND_TOP - most top
									 HWND_NOTOPMOST - right under of most top window
									 HWND_BOTTOM - most bottop(back) z position
				  x, //coordinate x
				  y, //coordinate y
				  cx, //width size
				  cy, //height size
				  uFlags // SWP_NOMOVE - no change in coordinate(ignore argument x, y),  SWP_NOZORDER - keep current z position(ignore hWndInsertAfter arguments)
	*/
   SetWindowPos(hWnd,
	   HWND_TOPMOST,
	   100,
	   100,
	   g_ClientRECT.right - g_ClientRECT.left, //808-(-8)  == 816px
	   g_ClientRECT.bottom - g_ClientRECT.top, //608-(-31) == 639px
	   SWP_NOMOVE | SWP_NOZORDER);
   //end -- initialize client area --

   
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		SendMessage(hWnd, WM_CLOSE, NULL, NULL); //PostQuitMessage(0); has memory leak issues so replaced.
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


void Run()
{
	InitDeltaTime();

	//player speed per second
	g_fPlayerSpeed = (300 * g_fDeltaTime) * g_fTimeScale;
	//g_fPlayerSpeed = (300 + 300 * 0.05f) * g_fDeltaTime * g_fTimeScale; // - 5% speed up  , when player enhanced  5% speed up item , 90% == 0.9f
	

	//Rendering
	Rendering();

	KeyboardInteract();


	

}


void KeyboardInteract()
{
	/*
	GetAsyncKeyState('W') - check key pressed or none and return state
	first press 0x8001
	sequance press 0x8000

	  if( GetAsyncKeyState( VK_LEFT ) & 0x8000) {
	  //move left logic
	  }

	*/
	if (RightInput('D')) //move right
	{
		g_tPlayerSquare.left += g_fPlayerSpeed;
		g_tPlayerSquare.right += g_fPlayerSpeed;
	}
	if (LeftInput('A')) //move left
	{
		g_tPlayerSquare.left -= g_fPlayerSpeed;
		g_tPlayerSquare.right -= g_fPlayerSpeed;
	}
	if (DownInput('S')) //move down
	{
		g_tPlayerSquare.top += g_fPlayerSpeed;
		g_tPlayerSquare.bottom += g_fPlayerSpeed;
	}
	if (UpInput('W')) //move up
	{
		g_tPlayerSquare.top -= g_fPlayerSpeed;
		g_tPlayerSquare.bottom -= g_fPlayerSpeed;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) //quit program
	{
		g_bLoop = false;
	}
	//begin - TimeScale
	if (GetAsyncKeyState(VK_F3) & 0x8000) //TimeScale - slower
	{
		g_fTimeScale -= g_fDeltaTime;
		if (g_fTimeScale < 0.f)
			g_fTimeScale = 0.f;
	}
	if (GetAsyncKeyState(VK_F4) & 0x8000) //TimeScale - faster
	{
		g_fTimeScale += g_fDeltaTime;
		if (g_fTimeScale > 1.f)
			g_fTimeScale = 1.f;
	}
	//end - TimeScale
	
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		fRECTANGLE rcBullet;
		rcBullet.left = g_tPlayerSquare.right;
		rcBullet.right = g_tPlayerSquare.right + 50.f;
		rcBullet.top = (g_tPlayerSquare.top + g_tPlayerSquare.bottom) / 2.f - 25.f;
		rcBullet.bottom = rcBullet.top + 50.f;
		g_PlayerBulletList.push_back(rcBullet);
	}
	


}


void InitDeltaTime()
{
	//get Delta time
	LARGE_INTEGER tTime;
	QueryPerformanceCounter(&tTime);
	g_fDeltaTime = (tTime.QuadPart - g_tTime.QuadPart) / static_cast<float>(g_tSecond.QuadPart);
	g_tTime = tTime;
}



void Rendering() {

	//Drawing Player
	Rectangle(g_hDC,
		static_cast<int>(g_tPlayerSquare.left),
		static_cast<int>(g_tPlayerSquare.top),
		static_cast<int>(g_tPlayerSquare.right),
		static_cast<int>(g_tPlayerSquare.bottom));



	//Drawing Player Bullet
	list<fRECTANGLE>::iterator iter;
	list<fRECTANGLE>::iterator iterEnd = g_PlayerBulletList.end();
	float fSpeed = 600.f * g_fDeltaTime * g_fTimeScale;

	for (iter = g_PlayerBulletList.begin(); iter != iterEnd; ++iter) // Player Bullet Moving
	{
		(*iter).left += fSpeed;
		(*iter).right += fSpeed;
	}
	for (iter = g_PlayerBulletList.begin(); iter != iterEnd; ++iter)
	{
		Rectangle(g_hDC,
			static_cast<int>((*iter).left),
			static_cast<int>((*iter).top),
			static_cast<int>((*iter).right),
			static_cast<int>((*iter).bottom));
	}
}