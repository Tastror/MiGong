#include "Scenery.h"
#include <iostream>

Scenery::Scenery()
{
	speed = 10;
	begin_mx = end_mx = sx = dest_sx = 0;
	begin_my = end_my = sy = dest_sy = 0;
	for (int i = 0; i < Radix; ++i)
		for (int j = 0; j < Radix2; ++j)
			material.push_back(0);
	valid = false;
	return;
}

Scenery::~Scenery()
{
	material.empty();
	return;
}

void Scenery::Push(MapTextureLayer* MTL, int LN)
{
	if (MTL == nullptr || LN < 0) return;
	valid = true;
	bondTextureLayer = MTL;
	bondLayerNum = LN;
	sw = bondTextureLayer->LayerElement[bondLayerNum].tw;
	sh = bondTextureLayer->LayerElement[bondLayerNum].th;
	return;
}

void Scenery::SynXY()
{
	if (!valid) return;
	sx = dest_sx;
	sy = dest_sy;
	bondTextureLayer->LayerElement[bondLayerNum].tx = -dest_sx;
	bondTextureLayer->LayerElement[bondLayerNum].ty = -dest_sy;
	
	return;
}

void Scenery::SlowSynXY()
{
	if (!valid) return;
	sx = (sx + dest_sx) / 2;
	sy = (sy + dest_sy) / 2;
	// if (sx - dest_sx < 2 && dest_sx - sx < 2) sx = dest_sx;
	// if (sy - dest_sy < 2 && dest_sy - sy < 2) sy = dest_sy;
	bondTextureLayer->LayerElement[bondLayerNum].tx = -sx;
	bondTextureLayer->LayerElement[bondLayerNum].ty = -sy;
	return;
}

void Scenery::Move(int dx, int dy)
{
	if (!valid) return;
	dest_sx += dx * speed;
	dest_sy += dy * speed;
	return;
}

void Scenery::AddMaterial(int x, int y)
{
	int mx = (x + sx) / ScenCell;
	int my = (y + sy) / ScenCell;
	if (mx * Radix + my < 0 || mx * Radix + my > Radix * Radix2)
		return;
	material[mx * Radix + my]++;
	if (material[mx * Radix + my] >= 4)
		material[mx * Radix + my] %= 4;
	return;
}

void Scenery::AddMXYMaterial(int mx, int my)
{
	if (mx * Radix + my < 0 || mx * Radix + my > Radix * Radix2)
		return;
	material[mx * Radix + my]++;
	if (material[mx * Radix + my] >= 4)
		material[mx * Radix + my] %= 4;
	return;
}

void Scenery::FindBE()
{
	for (int i = 0; i < Radix; ++i)
		for (int j = 0; j < Radix2; ++j)
			if (material[i * Radix + j] == 2)
			{
				begin_mx = i;
				begin_my = j;
				break;
			}
	for (int i = 0; i < Radix; ++i)
		for (int j = 0; j < Radix2; ++j)
			if (material[i * Radix + j] == 3)
			{
				end_mx = i;
				end_my = j;
				break;
			}
	return;
}
