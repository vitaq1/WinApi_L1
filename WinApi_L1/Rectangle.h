
#include <windows.h>
#include <gdiplus.h>
#include <iostream>

class MyRect
{

public:
	RECT rect;
	bool isMoving = false;
	bool mouseFollowing = false;
	int dx = 5, dy = 5;
	int width, height;

	MyRect(int left, int top, int right, int bottom) {
		rect.left = left;
		rect.right = right;
		rect.top = top;
		rect.bottom = bottom;

		width = left - right;
		height = bottom - top;
	}



	void moveLeft(RECT windowSize) {
		if (windowSize.left < rect.left)
		{
			OffsetRect(&rect, -10, 0);
		}
	}

	void moveRight(RECT windowSize) {
		if (windowSize.right > rect.right)
		{
			OffsetRect(&rect, 10, 0);
		}
	}

	void moveTop(RECT windowSize) {
		if (windowSize.top < rect.top)
		{
			OffsetRect(&rect, 0, -10);
		}
	}

	void moveBottom(RECT windowSize) {
		if (windowSize.bottom > rect.bottom)
		{
			OffsetRect(&rect, 0, 10);
			
		}
	}

	void moveTo(RECT windowSize, int x, int y) {

		if (windowSize.left < x + width / 2 && windowSize.right > x - width / 2 && windowSize.top < y - height / 2 && windowSize.bottom > y + height / 2)
		{
			rect.left = x + width / 2;
			rect.right = x - width / 2;
			rect.top = y - height / 2;
			rect.bottom = y + height / 2;
		}
	}

	void autoMove(RECT windowSize) {
		OffsetRect(&rect, dx, dy);
		if (windowSize.left > rect.left) dx = -dx;
		if (windowSize.right < rect.right) dx = -dx;
		if (windowSize.top > rect.top) dy = -dy;
		if (windowSize.bottom < rect.bottom) dy = -dy;
	}

	void loadImage(HDC hdc) {

		Gdiplus::Graphics gf(hdc);
		Gdiplus::Bitmap bmp(L"C:\\Users\\User\\Desktop\\cat.png");
		gf.DrawImage(&bmp, 50, 100);

	}


};
