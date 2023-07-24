#ifndef _TextureLayer_H_
#define _TextureLayer_H_

#include "SDLQuickLoad.h"

class Animation {
public:
	#define MaxAnime 20
	SDL_Texture* tex[MaxAnime];
	SDL_Rect rec[MaxAnime];
	int AnimeNum;
	int speed;
public:
	void Compose(Texture* ntex);
	void Compose(WordTexture* ntex);
	void Pop();
public:
	Animation();
};

struct LayerElement_TP {
	Animation *ani;
	int nowNum;
	int current;
	int tx;
	int ty;
	int tw;
	int th;
	bool use;
};

class TextureLayer {
public:
	SDL_Renderer* bond_renderer;
public:
	#define MaxLayer 200
	int layerNum;
	LayerElement_TP LayerElement[MaxLayer];
public:
	void Update();
	void Push(Animation* nAni, int x, int y);
	void Pop();
	int PreNumber();
public:
	TextureLayer(SDL_Renderer* renderer);
};

class MapTextureLayer {
public:
	SDL_Renderer* bond_renderer;
public:
	#define MaxMapLayer 8000
	int layerNum;
	LayerElement_TP LayerElement[MaxMapLayer];
public:
	void Update();
	void Push(Animation* nAni, int x, int y);
	void Pop();
	int PreNumber();
public:
	MapTextureLayer(SDL_Renderer* renderer);
};

#endif
