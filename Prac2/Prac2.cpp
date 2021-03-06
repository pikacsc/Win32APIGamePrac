// Prac2.cpp : Define entry point

#include "stdafx.h"
#include "Prac2.h"

#define MAX_LOADSTRING 100

// Global variables
HINSTANCE hInst;                                // current instance 
WCHAR szTitle[MAX_LOADSTRING];                  // title text
WCHAR szWindowClass[MAX_LOADSTRING];            // window class name 


// HINSTANCE : Every window process has own HINSTANCE, so that OS(window) can distinguish each window process. Kernel Object(Warning no touch)



// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);



struct _tagArea
{
	bool  bStart;
	POINT ptStart; //start point
	POINT ptEnd;   //end point
};

_tagArea g_tArea;




int APIENTRY wWinMain(_In_ HINSTANCE hInstance, 
                     _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    
    // Global string object initialize
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PRAC2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRAC2));

    MSG msg;

    //basic message loop
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


//   MyRegisterClass(): To Register Window class
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRAC2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL; //MAKEINTRESOURCEW(IDC_PRAC2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//   InitInstance(HINSTANCE, int): 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//	WndProc(HWND, UINT, WPARAM, LPARAM) : To handle messages
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
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
	case WM_MOUSEMOVE: //Mouse moving
		if (g_tArea.bStart)
		{
			g_tArea.ptEnd.x = lParam & 0x0000ffff;
			g_tArea.ptEnd.y = lParam >> 16;
			InvalidateRect(hWnd, NULL, true);
		}
		break;
	case WM_LBUTTONDOWN: // Mouse left button pressed
		if (!g_tArea.bStart)
		{
			g_tArea.bStart = true;
			g_tArea.ptStart.x = lParam & 0x0000ffff; //lParam : mouse position
			g_tArea.ptStart.y = lParam >> 16;
			g_tArea.ptEnd = g_tArea.ptStart;

			/*InvalidateRect(...) - forcefully call WM_PAINT message
			InvalidateRect(hWnd, 
							 NULL, - renew area if NULL then entire window screen area
							 true); - If true then erase current screen and renewing
							          If False then no erase renewing
			
			*/
			InvalidateRect(hWnd, NULL, true);
		}
		break;
	case WM_LBUTTONUP: //after pressed Mouse left button then releasd 
		if (g_tArea.bStart)
		{
			g_tArea.bStart = false;
			g_tArea.ptEnd.x = lParam & 0x0000ffff;
			g_tArea.ptEnd.y = lParam >> 16;
			InvalidateRect(hWnd, NULL, true);
		}
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

			//TextOut(hdc, x, y, string, string length to print); - Print text on window
			TextOut(hdc, 50, 50, TEXT("Hello"), 5); //unicode string : L"" or TEXT("")
			

			//Rectangle(hdc, a, b, x,y);  - draw diagonal from (a, b) to (x, y) and draw rectangle on diagonal.
			Rectangle(hdc, 100, 100, 200, 200);

			//MoveToEx(hdc, x, y, previous point pointer not always necessary) - move "current coordinate" to (x,y)
			MoveToEx(hdc, 100, 100, NULL);

			//LineTo(hdc,a,b) - draw line from "current coordinate"(x,y) to (a,b)
			LineTo(hdc, 200, 200);

			//Rectangle(hdc, a, b, x,y);  - draw diagonal from (a, b) to (x, y) and draw rectangle on diagonal.
			Rectangle(hdc, 100, 100, 200, 200);

			//Ellipse(hdc, a,b , x,y ); - draw exactly fitted circle inside of Rectangle(hdc, a,b , x,y)
			Ellipse(hdc, 100, 100, 200, 200);


			MoveToEx(hdc, 400, 500, NULL);
			LineTo(hdc, 100, 400);
			Ellipse(hdc, 400, 500, 100, 400);



			TCHAR strMouse[64] = {};
			
			//wsprinf(TCHAR [], TEXT("%d"), int variable or other variable to use format specifier %d, %c, %s) - make unicode string
			wsprintf(strMouse, TEXT("x : %d  y : %d"), g_tArea.ptStart.x, g_tArea.ptStart.y); 

			TextOut(hdc, 600, 30, strMouse, lstrlen(strMouse)); //lstrlen(unicode string) - get length of unicode string


			//draw rectangle like a window mouse or starcraft
			if (g_tArea.bStart)
			{
				Rectangle(hdc, g_tArea.ptStart.x, g_tArea.ptStart.y, g_tArea.ptEnd.x, g_tArea.ptEnd.y);
			}


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

// 정보 대화 상자의 메시지 처리기입니다.
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
