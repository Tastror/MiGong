#include "Props.h"

Props::Props(Scenery* BS, MapTextureLayer* MTL, int BTN):
	bondScenery(BS), bondTextureLayer(MTL), beginLayerNum(BTN)
{
	nowPropsNum = 0;
	nowLayerNum = beginLayerNum + nowPropsNum;
	return;
}

void Props::Push(int mx, int my)
{
	// mx * ScenCell + ScenCell / 2 = px + pw / 2
	// my * ScenCell + ScenCell = py + ph
	if (nowPropsNum >= PropsNum) return;
	PropsTex[nowPropsNum].pmx = mx;
	PropsTex[nowPropsNum].pmy = my;
	PropsTex[nowPropsNum].pw = bondTextureLayer->LayerElement[nowLayerNum].tw;
	PropsTex[nowPropsNum].ph = bondTextureLayer->LayerElement[nowLayerNum].th;
	PropsTex[nowPropsNum].px = mx * ScenCell + ScenCell / 2 - PropsTex[nowPropsNum].pw / 2;
	PropsTex[nowPropsNum].py = my * ScenCell + ScenCell / 2 - PropsTex[nowPropsNum].ph;
	bondTextureLayer->LayerElement[nowLayerNum].use = true;
	nowPropsNum++;
	nowLayerNum = beginLayerNum + nowPropsNum;
	return;
}

void Props::SynXY()
{
	for (int i = 0; i < nowPropsNum; ++i)
	{
		bondTextureLayer->LayerElement[i + beginLayerNum].tx = PropsTex[i].px - bondScenery->sx;
		bondTextureLayer->LayerElement[i + beginLayerNum].ty = PropsTex[i].py - bondScenery->sy;
	}
	return;
}

void Props::Empty()
{
	for (int i = beginLayerNum; i < nowLayerNum; ++i)
		bondTextureLayer->LayerElement[i].use = false;
	nowPropsNum = 0;
	nowLayerNum = beginLayerNum + nowPropsNum;
	return;
}

void Props::LoadInScen(int code)
{
	Empty();
	for (int zx = 0; zx < Radix; ++zx)
		for (int zy = 0; zy < Radix2; ++zy)
			if (zx * Radix + zy >= 0 && zx * Radix + zy <= Radix * Radix2)
			if (bondScenery->material[zx * Radix + zy] == code)
			{
				// std::cout << zx << ", " << zy << std::endl;
				Push(zx, zy);
			}
	return;
}

void Props::LoadInScen2(int code)
{
	Empty();
	for (int zx = 0; zx < Radix; ++zx)
		for (int zy = 0; zy < (Height / ScenCell + 3); ++zy)
			if (bondScenery->material[zx * Radix + zy] == code)
			{
				// std::cout << zx << ", " << zy << std::endl;
				Push2(zx, zy);
			}
	return;
}

void Props::Push2(int mx, int my)
{
	// mx * ScenCell = px
	// my * ScenCell = py
	if (nowPropsNum >= PropsNum) return;
	PropsTex[nowPropsNum].pmx = mx;
	PropsTex[nowPropsNum].pmy = my;
	PropsTex[nowPropsNum].pw = bondTextureLayer->LayerElement[nowLayerNum].tw;
	PropsTex[nowPropsNum].ph = bondTextureLayer->LayerElement[nowLayerNum].th;
	PropsTex[nowPropsNum].px = mx * ScenCell;
	PropsTex[nowPropsNum].py = my * ScenCell;
	bondTextureLayer->LayerElement[nowLayerNum].use = true;
	nowPropsNum++;
	nowLayerNum = beginLayerNum + nowPropsNum;
	return;
}
