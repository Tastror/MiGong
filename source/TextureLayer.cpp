#include "TextureLayer.h"

Animation::Animation()
{
	// SDL_Rect rec = { 0, 0, 0, 0 };
	AnimeNum = 0;
	speed = 10;
	return;
}

void Animation::Compose(Texture* ntex)
{
	if (AnimeNum >= MaxAnime)
		return;
	rec[AnimeNum].w = ntex->GetWidth();
	rec[AnimeNum].h = ntex->GetHeight();
	tex[AnimeNum] = ntex->GetTexture();
	AnimeNum++;
	return;
}

void Animation::Compose(WordTexture* ntex)
{
	if (AnimeNum >= MaxAnime)
		return;
	rec[AnimeNum].w = ntex->GetWidth();
	rec[AnimeNum].h = ntex->GetHeight();
	tex[AnimeNum] = ntex->GetTexture();
	AnimeNum++;
	return;
}

void Animation::Pop()
{
	if (AnimeNum <= 0)
		return;
	AnimeNum--;
	return;
}

TextureLayer::TextureLayer(SDL_Renderer* renderer): bond_renderer(renderer)
{
	layerNum = 0;
	return;
}

void TextureLayer::Update()
{
	for (int i = 0; i < layerNum; ++i)
	{
		if (!LayerElement[i].use)
			continue;
		LayerElement[i].current++;
		LayerElement[i].current %= LayerElement[i].ani->AnimeNum * LayerElement[i].ani->speed;
		LayerElement[i].nowNum = LayerElement[i].current / LayerElement[i].ani->speed;
		// 长宽*不按*动画第一张图计算，而是按上一张计算
		SDL_Rect rec = { LayerElement[i].tx, LayerElement[i].ty, LayerElement[i].ani->rec[LayerElement[i].nowNum].w, LayerElement[i].ani->rec[LayerElement[i].nowNum].h };
		SDL_RenderCopy(bond_renderer, LayerElement[i].ani->tex[LayerElement[i].nowNum], NULL, &rec);
	}
	return;
}

void TextureLayer::Push(Animation* nAni, int x, int y)
{
	if (layerNum >= MaxLayer)
		return;
	LayerElement[layerNum].use = true;
	LayerElement[layerNum].tx = x;
	LayerElement[layerNum].ty = y;
	// 长宽按动画第一张图计算
	LayerElement[layerNum].tw = nAni->rec[0].w;
	LayerElement[layerNum].th = nAni->rec[0].h;
	LayerElement[layerNum].current = 0;
	LayerElement[layerNum].nowNum = 0;
	LayerElement[layerNum].ani = nAni;
	layerNum++;
	return;
}

void TextureLayer::Pop()
{
	if (layerNum > 0)
		layerNum--;
	return;
}

int TextureLayer::PreNumber()
{
	return layerNum - 1;
}



MapTextureLayer::MapTextureLayer(SDL_Renderer* renderer): bond_renderer(renderer)
{
	layerNum = 0;
	return;
}

void MapTextureLayer::Update()
{
	for (int i = 0; i < layerNum; ++i)
	{
		if (!LayerElement[i].use)
			continue;
		LayerElement[i].current++;
		LayerElement[i].current %= LayerElement[i].ani->AnimeNum * LayerElement[i].ani->speed;
		LayerElement[i].nowNum = LayerElement[i].current / LayerElement[i].ani->speed;
		// 长宽*不按*动画第一张图计算，而是按上一张计算
		SDL_Rect rec = { LayerElement[i].tx, LayerElement[i].ty, LayerElement[i].ani->rec[LayerElement[i].nowNum].w, LayerElement[i].ani->rec[LayerElement[i].nowNum].h };
		SDL_RenderCopy(bond_renderer, LayerElement[i].ani->tex[LayerElement[i].nowNum], NULL, &rec);
	}
	return;
}

void MapTextureLayer::Push(Animation* nAni, int x, int y)
{
	if (layerNum >= MaxMapLayer)
		return;
	LayerElement[layerNum].use = true;
	LayerElement[layerNum].tx = x;
	LayerElement[layerNum].ty = y;
	// 长宽按动画第一张图计算
	LayerElement[layerNum].tw = nAni->rec[0].w;
	LayerElement[layerNum].th = nAni->rec[0].h;
	LayerElement[layerNum].current = 0;
	LayerElement[layerNum].nowNum = 0;
	LayerElement[layerNum].ani = nAni;
	layerNum++;
	return;
}

void MapTextureLayer::Pop()
{
	if (layerNum > 0)
		layerNum--;
	return;
}

int MapTextureLayer::PreNumber()
{
	return layerNum - 1;
}
