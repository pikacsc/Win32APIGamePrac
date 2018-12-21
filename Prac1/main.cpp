#include <Windows.h> //To use WinMain() and other win32API 

int CALLBACK WinMain(_In_ HINSTANCE hInstance,_In_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nCmdShow)
{
//int MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
	  MessageBoxA(NULL     , "HelloWorld" , "MessageBox"    , MB_OK     );
}


