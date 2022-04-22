#ifndef _Character_H_
#define _Character_H_

#include "Scenery.h"
#include <ctime>
#include <cstdio>

class Character {
private:
	bool valid;
public:
	Scenery* bondScenery;
	#define CharNum 10
	struct Bond_Tex_TP {
		MapTextureLayer* bondTextureLayer;
		int bondLayerNum;
	} CharTex[CharNum];
	int nowCharNum;
public:
	int cx;
	int cy;
	int cw;
	int ch;
	int cmx;
	int cmy;
	int faceDirection;
	int speed;
	// home character x;
	int home_cx;
	int home_cy;
	bool win;
public:
	void Push(MapTextureLayer* MTL, int LN);
	void SynXY();
	void SynMXY();
	void LockSight();
	void RandomReborn();
	void Move(int dx, int dy);
public:
	Character(Scenery* BS);
};

#endif
