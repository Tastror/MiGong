#include "Character.h"

Character::Character(Scenery* BS):
	bondScenery(BS)
{
	valid = false;
	nowCharNum = 0;
	cx = 0;
	cy = 0;
	cw = 0;
	ch = 0;
	cmx = 0;
	cmy = 0;
	faceDirection = 1;
	speed = 4;
	home_cx = 0;
	home_cy = 0;
	win = false;
	return;
}

void Character::Push(MapTextureLayer* MTL, int LN)
{
	if (MTL == nullptr || LN < 0) return;
	if (nowCharNum >= CharNum) return;
	valid = true;
	CharTex[nowCharNum].bondTextureLayer = MTL;
	CharTex[nowCharNum].bondLayerNum = LN;
	// 角色可能有很多方向，所以就写了push来绑定多个图层。 
	// 其中，长宽按照最近绑定的那个图层动画计算。 
	cw = CharTex[nowCharNum].bondTextureLayer->LayerElement[CharTex[nowCharNum].bondLayerNum].tw;
	ch = CharTex[nowCharNum].bondTextureLayer->LayerElement[CharTex[nowCharNum].bondLayerNum].th;
	CharTex[nowCharNum].bondTextureLayer->LayerElement[CharTex[nowCharNum].bondLayerNum].use = true;
	nowCharNum++;
	return;
}

void Character::SynXY()
{
	// cmx * ScenCell + ScenCell / 2 = cx + cw / 2
	// cmy * ScenCell + ScenCell = cy + ch
	if (!valid) return;
	for (int i = 0; i < nowCharNum; ++i)
	{
		CharTex[i].bondTextureLayer->LayerElement[CharTex[i].bondLayerNum].tx = cx - bondScenery->sx;
		CharTex[i].bondTextureLayer->LayerElement[CharTex[i].bondLayerNum].ty = cy - bondScenery->sy;
		// std::cout << CharTex[i].bondTextureLayer->LayerElement[CharTex[i].bondLayerNum].tx << ", " << CharTex[i].bondTextureLayer->LayerElement[CharTex[i].bondLayerNum].ty << std::endl;
	}
	SynMXY();
	return;
}

void Character::SynMXY()
{
	cmx = (cx + cw / 2) / ScenCell;
	cmy = (cy + ch) / ScenCell;
	return;
}

void Character::LockSight()
{
	bondScenery->dest_sx = cx + cw / 2 - 900 / 2;
	if (bondScenery->dest_sx > Width - 900 + 25)
		bondScenery->dest_sx = Width - 900 + 25;
	if (bondScenery->dest_sx < -25)
		bondScenery->dest_sx = -25;
	bondScenery->dest_sy = cy + ch / 2 - 600 / 2;
	if (bondScenery->dest_sy > Height - 600 + 25)
		bondScenery->dest_sy = Height - 600 + 25;
	if (bondScenery->dest_sy < -25)
		bondScenery->dest_sy = -25;
	return;
}

void Character::RandomReborn()
{
	srand(SDL_GetTicks());
	do
	{
		cx = 50 + rand() % (Width - 100);
		cy = 50 + rand() % (Height - 100);
		SynMXY();
		if (cmx * Radix + cmy >= 0 && cmx * Radix + cmy <= Radix * Radix2)
			continue;
	} while (bondScenery->material[cmx * Radix + cmy]);
	home_cx = cx;
	home_cy = cy;
	win = false;
	return;
}

void Character::Move(int dx, int dy)
{
	if (!valid) return;
	int precx = cx, precy = cy;
	cx += dx * speed;
	cy += dy * speed;
	SynMXY();
	if (cx > Width - cw) cx = Width - cw;
	if (cx < 0) cx = 0;
	if (cy > Height - ch - ScenCell / 2) cy = Height - ch - ScenCell / 2;
	if (cy < -ch) cy = -ch;
	win = false;
	if (cmx * Radix + cmy >= 0 && cmx * Radix + cmy <= Radix * Radix2)
	{
		if (bondScenery->material[cmx * Radix + cmy] == 1)
			cx = precx, cy = precy, SynMXY();
		if (bondScenery->material[cmx * Radix + cmy] == 3)
			win = true;
	}
	// std::cout << win << std::endl;
	return;
}
