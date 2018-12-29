#include "stdafx.h"
#include "Prac3.h"
#define MAX_LOADSTRING 100

HINSTANCE hInst;                               
WCHAR szTitle[MAX_LOADSTRING];                 
WCHAR szWindowClass[MAX_LOADSTRING];           
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND				g_hWnd; //initialize global window handle variable
bool				g_bLoop = true; // To use g_bLoop instead "GetMessage(&msg, nullptr, 0, 0)" in Message loop
HDC					g_hDC;
RECT				g_tPlayerSquare = {100,100,200,200}; //Player, SquareShape
RECT				clientRectangle;
void Run(); // Game Running function
void KeyboardInteract(); // Keyboard input interact, W, A, S, D ...
inline bool LeftInput  (char left )  {
	GetClientRect(g_hWnd, &clientRectangle);
	return (GetAsyncKeyState(left)  & 0x8000) && (g_tPlayerSquare.left  > clientRectangle.left);
}
inline bool RightInput (char right)  { 
	GetClientRect(g_hWnd, &clientRectangle);
	return (GetAsyncKeyState(right) & 0x8000) && (g_tPlayerSquare.right  < clientRectangle.right);
}
inline bool UpInput	   (char Up   )  { 
	GetClientRect(g_hWnd, &clientRectangle);
	return (GetAsyncKeyState(Up)    & 0x8000) && (g_tPlayerSquare.top    > clientRectangle.top);
}
inline bool DownInput  (char Down )  { 
	GetClientRect(g_hWnd, &clientRectangle);
	return (GetAsyncKeyState(Down)  & 0x8000) && (g_tPlayerSquare.bottom < clientRectangle.bottom);
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

	g_hDC = GetDC(g_hWnd); // initialize window DC, Warning, to avoid memory leak, you must "ReleaseDC(g_hWnd,g_hDC)" at the end.

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRAC3));

    MSG msg;

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
   clientRectangle = { 0, 0, 800, 600 };
   AdjustWindowRect(&clientRectangle, WS_OVERLAPPEDWINDOW, FALSE);// Get size of window screen including title bar and men;

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
	   clientRectangle.right - clientRectangle.left, //808-(-8)  == 816px
	   clientRectangle.bottom - clientRectangle.top, //608-(-31) == 639px
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
        PostQuitMessage(0);
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
	// draw Player
	Rectangle(g_hDC, g_tPlayerSquare.left, g_tPlayerSquare.top, g_tPlayerSquare.right, g_tPlayerSquare.bottom);
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
		g_tPlayerSquare.left += 1;
		g_tPlayerSquare.right += 1;
	}
	if (LeftInput('A')) //move left
	{
		g_tPlayerSquare.left -= 1;
		g_tPlayerSquare.right -= 1;
	}
	if (DownInput('S')) //move down
	{
		g_tPlayerSquare.top += 1;
		g_tPlayerSquare.bottom += 1;
	}
	if (UpInput('W')) //move up
	{
		g_tPlayerSquare.top -= 1;
		g_tPlayerSquare.bottom -= 1;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) //quit program
	{
		g_bLoop = false;
	}


}


