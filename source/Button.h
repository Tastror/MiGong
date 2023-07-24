#ifndef _Button_H_
#define _Button_H_

#include "TextureLayer.h"

class Button{
public:
	SDL_Rect rec[100];
	int recNum;
	int nowIn;
	int click;
public:
	void Add(int x, int y, int w, int h);
	void Add2(int x, int y, int x2, int y2);
	bool In(int x, int y);
	bool Click(int x, int y);
public:
	Button();
};

#endif
