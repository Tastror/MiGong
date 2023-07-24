#include "Button.h"

Button::Button()
{
	recNum = 0;
	nowIn = -1;
	click = -1;
	return;
}

void Button::Add(int x, int y, int w, int h)
{
	rec[recNum].x = x;
	rec[recNum].y = y;
	rec[recNum].w = w;
	rec[recNum].h = h;
	recNum++;
	return;
}

void Button::Add2(int x, int y, int x2, int y2)
{
	rec[recNum].x = x;
	rec[recNum].y = y;
	rec[recNum].w = x2 - x;
	rec[recNum].h = y2 - y;
	recNum++;
	return;
}

bool Button::In(int x, int y)
{
	for (int i = recNum - 1; i >= 0; --i)
	{
		if (x >= rec[i].x && x <= rec[i].x + rec[i].w
			&& y >= rec[i].y && y <= rec[i].y + rec[i].h)
		{
			nowIn = i;
			return true;
		}
	}
	nowIn = -1;
	return false;
}

bool Button::Click(int x, int y)
{
	for (int i = recNum - 1; i >= 0; --i)
	{
		if (x >= rec[i].x && x <= rec[i].x + rec[i].w
			&& y >= rec[i].y && y <= rec[i].y + rec[i].h)
		{
			click = i;
			return true;
		}
	}
	click = -1;
	return false;
}
