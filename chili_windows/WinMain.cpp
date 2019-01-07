#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <Windowsx.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "resource.h"

constexpr auto WIN_CLASS_NAME = "wndClass1";
HINSTANCE hInstance_app = NULL;

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
	winClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(ID_ICON1));
	winClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(ID_CURSOR1));
	winClass.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	winClass.lpszClassName = WIN_CLASS_NAME;
	winClass.lpszMenuName = NULL;	
	winClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(ID_ICON1));

	hInstance_app = hInstance;

	if (!RegisterClassEx(&winClass))
		return 0;

	if (!(hWnd = CreateWindowEx(NULL, WIN_CLASS_NAME,
		"My first window",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0,0,400,400,
		NULL, 
		LoadMenu(hInstance, "soundMenu"),
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

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case MENU_FILE_ID_EXIT:
				{
					PostQuitMessage(0);
				}break;

				case MENU_PLAY_ID_ENERGIZE:
				{
					PlaySound(MAKEINTRESOURCE(SOUND_ID_ENERGIZE), hInstance_app, SND_RESOURCE | SND_ASYNC);
				}break;

				case MENU_PLAY_ID_BEAM:
				{
					PlaySound(MAKEINTRESOURCE(SOUND_ID_BEAM), hInstance_app, SND_RESOURCE | SND_ASYNC);
				}break;

				case MENU_PLAY_ID_TELEPORT:
				{
					PlaySound(MAKEINTRESOURCE(SOUND_ID_TELEPORT), hInstance_app, SND_RESOURCE | SND_ASYNC);
				}break;

				case MENU_PLAY_ID_WARP:
				{
					PlaySound(MAKEINTRESOURCE(SOUND_ID_WARP), hInstance_app, SND_RESOURCE | SND_ASYNC);
				}break;

				case MENU_HELP_ID_ABOUT:
				{
					MessageBox(hWnd, "Menu sound demo", "About sound programm", MB_OK | MB_ICONEXCLAMATION);
				}break;

				default: break;
			}
		}break;
	

		case WM_DESTROY:
		{		
			PlaySound(NULL, hInstance_app, SND_PURGE|SND_SYNC);
			PostQuitMessage(69);
			return 0;
		}
		break;

		default:break;
	}

	return(DefWindowProc(hWnd, msg, wParam, lParam));

}