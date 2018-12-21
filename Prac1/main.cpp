#include <Windows.h> //To use WinMain() and other win32API 

//basic form of function WndProc()
LRESULT CALLBACK MyWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage) {
	case WM_LBUTTONDOWN://mouse left button pressed
		MessageBoxA(0, "Boom!", "You just clicked left Button!", MB_OK);
		return 0;
	/*
	case Every action can be messages, minimumize window, maximumize window, mouse click, hover etc:
		//effect
		return 0;
	*/

	case WM_DESTROY: //when press X button(destroy screen)
		MessageBoxA(0, "Good Bye!", "You just clicked X Button!", MB_OK);
		PostQuitMessage(0); //destroy process
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); //DefWindowProc() : dealing basic messages
}



int CALLBACK WinMain(_In_ HINSTANCE hInstance,_In_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nCmdShow)
{
//int MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
//	  MessageBoxA(NULL     , "HelloWorld" , "MessageBox"    , MB_OK     );

/*
	HWND CreateWindowA(
		LPCTSTR lpClassName, //built in window class name, "edit", "button", etc ... or custom RegisterClass name
		LPCTSTR lpWindowName, //window screen title name
		DWORD dwStyle, //window screen style
		int x,   //location of window screen based on horizontal x value
		int y,   //location of window screen based on vertical y value
		int nWidth, //window screen width size
		int nHeight, //window screen height size
		HWND hWndParent, // parent window handle, window screen will be draw on parent window, if NULL,then based on "Desktop"
		HMENU hMenu, // create menu bar, File, edit ,etc ... , if NULL,then no menu bar
		HINSTANCE hInstance, //instance handle which is dealing with window screen
		LPVOID lpParam);
*/

	/*
	ATOM RegisterClassA(
		const WNDCLASSA *lpWndClass
	);
	*/
	WNDCLASSA WndClass = { 0 };
	WndClass.lpszClassName = "MyWindow"; //Register Class Name , we can use it with CreateWindowA()
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = MyWndProc; //function which is dealing window message queue
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //set background color
	
	/*
	typedef struct tagWNDCLASSA {
	UINT      style;
	WNDPROC   lpfnWndProc;
	int       cbClsExtra;
	int       cbWndExtra;
	HINSTANCE hInstance;
	HICON     hIcon;
	HCURSOR   hCursor;
	HBRUSH    hbrBackground;
	LPCSTR    lpszMenuName;
	LPCSTR    lpszClassName;
	} WNDCLASSA, *PWNDCLASSA, *NPWNDCLASSA, *LPWNDCLASSA;
	*/


	RegisterClassA(&WndClass);
	CreateWindowA("MyWindow","firtWindow",WS_OVERLAPPEDWINDOW|WS_VISIBLE,5,5,500,500,NULL,NULL,hInstance,NULL);
	

	/*
	BOOL GetMessage(
		LPMSG lpMsg,
		HWND  hWnd,
		UINT  wMsgFilterMin,
		UINT  wMsgFilterMax
	);
	
	*/

	MSG msg;

	while (GetMessageA(&msg, 0, NULL, NULL)) //GetMessageA() : get message from MessageQueue
	{
		DispatchMessageA(&msg); //dispatch message to WndProc()
	}
	
	//MessageBoxA(NULL, "test", "Now you see me", MB_OK);

	return 0;
}


