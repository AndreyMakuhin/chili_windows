#include <Windows.h>

constexpr auto WIN_CLASS_NAME = "wndClass1";

LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow) 
{
	WNDCLASSEX winClass;
	HWND hWnd;
	MSG msg;

	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	winClass.hInstance = hInstance;
	winClass.lpfnWndProc = wndProc;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	winClass.lpszClassName = WIN_CLASS_NAME;
	winClass.lpszMenuName = NULL;
	winClass.hIconSm = NULL;

	if (!RegisterClassEx(&winClass))
		return 0;

	if (!(hWnd = CreateWindowEx(NULL, WIN_CLASS_NAME,
		"My first window",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0,0,400,400,
		NULL, NULL,
		hInstance, NULL	)))
		return 0;

	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (msg)
	{
	case WM_CREATE:
	{
		return 0;
	}
	break;

	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;
	}
	break;

	case WM_DESTROY:
	{
		PostQuitMessage(69);
		return 0;
	}
	break;

	default:
		break;
	}

	return(DefWindowProc(hWnd, msg, wParam, lParam));

}