#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include "Rectangle.h"
#include "Image.h"

#pragma comment (lib,"Gdiplus.lib")


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void drawImage(HDC hdc);

HDC hdc;
HDC hdcCache;
HBITMAP bm;
RECT winCords;
MyRect rect(180, 100, 400, 300);
//Gdiplus::Image bmp(L"C:\\cat.png");
Gdiplus::Rect imRect(50, 50, 200, 140);
MyImage img(imRect);




int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);



	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Learn to Program Windows",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	MSG msg = { };
	HDC hdcc = GetDC(hwnd);
	hdcCache = CreateCompatibleDC(hdcc);
	bm = CreateCompatibleBitmap(hdcc, winCords.right, winCords.bottom);
	SelectObject(hdcCache, bm);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	Gdiplus::GdiplusShutdown(gdiplusToken);

	return 0;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода
	GetClientRect(hwnd, &winCords);


	Gdiplus::Image bmp = (L"C:\\cat.png");

	switch (uMsg)
	{

	case WM_PAINT:

		drawImage(hdcCache);
		FillRect(hdcCache, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		FillRect(hdcCache, &rect.rect, HBRUSH(CreateSolidBrush(RGB(255, 0, 55))));
		hdc = BeginPaint(hwnd, &ps);

		BitBlt(hdc, 0, 0, winCords.right, winCords.bottom, hdcCache, 0, 0, SRCCOPY);
		ValidateRect(hwnd, NULL);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			rect.moveLeft(winCords);
			img.moveLeft(winCords);
			break;
		case VK_RIGHT:
			rect.moveRight(winCords);
			img.moveRight(winCords);
			break;
		case VK_UP:
			rect.moveTop(winCords);
			img.moveTop(winCords);
			break;
		case VK_DOWN:
			rect.moveBottom(winCords);
			img.moveBottom(winCords);
			break;
		case VK_NUMPAD1:
			if (rect.isMoving)
			{
				KillTimer(hwnd, 1);
				rect.isMoving = false;
			}
			else {
				SetTimer(hwnd, 1, 16, nullptr);
				rect.isMoving = true;
			}

			if (img.isMoving)
			{
				KillTimer(hwnd, 2);
				img.isMoving = false;
			}
			else {
				SetTimer(hwnd, 2, 16, nullptr);
				img.isMoving = true;
			}
			break;
		case VK_NUMPAD2:

			break;
		default:
			break;
		}
		InvalidateRect(hwnd, NULL, FALSE);
		return 0;
	case WM_LBUTTONDOWN:
		if (LOWORD(lParam) > rect.rect.left && LOWORD(lParam) < rect.rect.right)
		{
			if (HIWORD(lParam) > rect.rect.top && HIWORD(lParam) < rect.rect.bottom)
			{
				rect.mouseFollowing = true;
			}
		};

		if (LOWORD(lParam) > img.rect.GetLeft() && LOWORD(lParam) < img.rect.GetRight())
		{
			if (HIWORD(lParam) > img.rect.GetTop() && HIWORD(lParam) < img.rect.GetBottom())
			{
				img.mouseFollowing = true;
			}
		};
		return 0;
	case WM_LBUTTONUP:
		rect.mouseFollowing = false;
		img.mouseFollowing = false;
		return 0;
	case WM_MOUSEMOVE:
		if (rect.mouseFollowing)
		{

			rect.moveTo(winCords, LOWORD(lParam), HIWORD(lParam));
			InvalidateRect(hwnd, NULL, FALSE);
		}

		if (img.mouseFollowing)
		{

			img.moveTo(winCords, LOWORD(lParam), HIWORD(lParam));
			InvalidateRect(hwnd, NULL, FALSE);
		}
		return 0;
	case WM_MOUSEWHEEL:
		if (LOWORD(wParam) == MK_SHIFT)
		{
			if (GET_WHEEL_DELTA_WPARAM(wParam) < 0) {
				rect.moveLeft(winCords);
				img.moveLeft(winCords);
			}
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) {
				rect.moveRight(winCords);
				img.moveRight(winCords);
			}
		}
		else
		{
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) {
				rect.moveTop(winCords);
				img.moveTop(winCords);
			}
			if (GET_WHEEL_DELTA_WPARAM(wParam) < 0) {
				rect.moveBottom(winCords);
				img.moveBottom(winCords);
			}
		}
		InvalidateRect(hwnd, NULL, FALSE);
		return 0;
	case WM_TIMER:
		rect.autoMove(winCords);
		img.autoMove(winCords);
		InvalidateRect(hwnd, NULL, FALSE);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


void drawImage(HDC hdc) {

	Gdiplus::Image bmp(L"C:\\cat.png");

	Gdiplus::Graphics gf(hdc);
	gf.Clear(Color::White);
	gf.DrawImage(&bmp, img.rect);

}




