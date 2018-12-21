#include <Windows.h> //To use WinMain() and other win32API 

int CALLBACK WinMain(_In_ HINSTANCE hInstance,_In_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nCmdShow)
{
//int MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
//	  MessageBoxA(NULL     , "HelloWorld" , "MessageBox"    , MB_OK     );

/*
	HWND CreateWindowA(
		LPCTSTR lpClassName, //built in window class name, "edit", "button", etc ...
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
	CreateWindowA("button","firtWindow",WS_POPUP|WS_VISIBLE,5,5,100,100,NULL,NULL,hInstance,NULL);
	MessageBoxA(NULL, "test", "Now you see me", MB_OK);

	return 0;
}


