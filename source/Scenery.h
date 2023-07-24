#ifndef _Scenery_H_
#define _Scenery_H_

#include "TextureLayer.h"
#include <vector>

#define Width 2000
#define Height 2000
#define ScenCell 25
#define Radix (Width / ScenCell + 3)
#define Radix2 (Height / ScenCell + 3)

class Scenery {
private:
	// 防止未初始化完全就用而导致出错，对之后的 Character 同理。 
	bool valid;
public:
	MapTextureLayer* bondTextureLayer;
	int bondLayerNum;
public:
	int sx;
	int sy;
	int sw;
	int sh;
	int speed;
	// destination scenery x;
	int dest_sx;
	int dest_sy;
	int begin_mx;
	int begin_my;
	int end_mx;
	int end_my;
public:
	std::vector<char> material;
public:
	void Push(MapTextureLayer* MTL, int LN);
	void SlowSynXY();
	void SynXY();
	void Move(int dx, int dy);
	void AddMaterial(int x, int y);
	void AddMXYMaterial(int mx, int my);
	void FindBE();
public:
	Scenery();
	~Scenery();
};

#endif
