#pragma once


#include <windows.h>
#include <gdiplus.h>
#include <iostream>
using namespace Gdiplus;

class MyImage
{

public:
	Rect rect;
	MyImage(Gdiplus::Rect rect) {
		this->rect = rect;
	}
	bool isMoving = false;
	bool mouseFollowing = false;
	int dx = 5, dy = 5;
	int width, height;

	void moveLeft(RECT windowSize) {
		if (windowSize.left < rect.GetLeft())
		{
			rect.Offset(-10, 0);


		}
	}

	void moveRight(RECT windowSize) {
		if (windowSize.right > rect.GetRight())
		{
			rect.Offset(10, 0);
		}
	}

	void moveTop(RECT windowSize) {
		if (windowSize.top < rect.GetTop())
		{
			rect.Offset(0, -10);
		}
	}

	void moveBottom(RECT windowSize) {
		if (windowSize.bottom > rect.GetBottom())
		{
			rect.Offset(0, 10);

		}
	}

	void moveTo(RECT windowSize, int x, int y) {

		if (windowSize.left < x + width / 2 && windowSize.right > x - width / 2 && windowSize.top < y - height / 2 && windowSize.bottom > y + height / 2)
		{
			rect.X = x;
			rect.Y = y;
			
		}
	}

	void autoMove(RECT windowSize) {
		rect.Offset(dx, dy);
		if (windowSize.left > rect.GetLeft()) dx = -dx;
		if (windowSize.right < rect.GetRight()) dx = -dx;
		if (windowSize.top > rect.GetTop()) dy = -dy;
		if (windowSize.bottom < rect.GetBottom()) dy = -dy;
	}

};