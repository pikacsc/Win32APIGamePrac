#include "Core.h"

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	if (!Core::GetIntance()->Init(hInstance))
	{
		Core::DestroyInstance();
		return 0;
	}

	int iRev = Core::GetIntance()->Run();

	Core::DestroyInstance();

	return iRev;
}