#ifndef _Props_H_
#define _Props_H_

#include "Scenery.h"

class Props {
public:
	Scenery* bondScenery;
	MapTextureLayer* bondTextureLayer;
	int beginLayerNum;
	int nowLayerNum;
	#define PropsNum 8000
	struct Bond_Tex_TP {
		int pmx;
		int pmy;
		int px;
		int py;
		int pw;
		int ph;
	} PropsTex[PropsNum];
	int nowPropsNum;
public:
	void Push(int mx, int my);
	void SynXY();
	void Empty();
	void LoadInScen(int code);
	void LoadInScen2(int code);
	void Push2(int mx, int my);
public:
	Props(Scenery* BS, MapTextureLayer* MTL, int BTN);
};

#endif
