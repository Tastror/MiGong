#include "SDLQuickLoad.h"

#define DEFAULT_FONT "../font/SuCaiJiShiKuFangTi.ttf"

#define SDLERROR(pointer) \
	if (pointer == nullptr) \
	{ \
		std::cout << SDL_GetError() << std::endl; \
		return; \
	}

#define TTFERROR(pointer) \
	if (pointer == nullptr) \
	{ \
		std::cout << TTF_GetError() << std::endl; \
		return; \
	}

#define SDLERRORNP() \
	{ \
	    std::cout << SDL_GetError() << std::endl; \
	    return; \
	}

#define TTFERRORNP() \
	{ \
	    std::cout << TTF_GetError() << std::endl; \
	    return; \
	}

/* **************** Window **************** */

Window::Window(const std::string& title, const int& width, const int& height):
Title(title.c_str()), SCREEN_WIDTH(width), SCREEN_HEIGHT(height)
{
	window = nullptr;
	renderer = nullptr;
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		/* send error */
		SDLERRORNP();
	window = SDL_CreateWindow(Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	/* send error */
	SDLERROR(window);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	/* send error */
	SDLERROR(renderer);
	if (TTF_Init() == -1)
		/* send error */
		TTFERRORNP();
	return;
}

Window::~Window()
{
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return;
}

const int Window::GetWidth() const
{
	return SCREEN_WIDTH;
}

const int Window::GetHeight() const
{
	return SCREEN_HEIGHT;
}

SDL_Renderer* Window::GetRenderer()
{
	return renderer;
}

SDL_Renderer* Window::gr()
{
	return renderer;
}

void Window::Clear()
{
	SDL_RenderClear(renderer);
	return;
}

void Window::Present()
{
	SDL_RenderPresent(renderer);
	return;
}

/* **************** Texture **************** */

Texture::Texture(SDL_Renderer* renderer)
{
	texture = nullptr;
	bond_renderer = renderer;
	rec.x = rec.y = rec.w = rec.h = 0;
	return;
}

Texture::~Texture()
{
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
	texture = nullptr;
	return;
}

void Texture::Load(const std::string& file)
{
	SDL_Surface* surface = SDL_LoadBMP(file.c_str());
	/* send error */
	SDLERROR(surface);
	texture = SDL_CreateTextureFromSurface(bond_renderer, surface);
	/* send error */
	SDLERROR(texture);
	SDL_QueryTexture(texture, NULL, NULL, &rec.w, &rec.h);
	SDL_FreeSurface(surface);
	return;
}

void Texture::LoadParent(const std::string& file, const SDL_Color& color)
{
	SDL_Surface* surface = SDL_LoadBMP(file.c_str());
	/* send error */
	SDLERROR(surface);
	Uint32 colorkey = SDL_MapRGB(surface->format, color.r, color.g, color.b);
	SDL_SetColorKey(surface, SDL_TRUE, colorkey);
	texture = SDL_CreateTextureFromSurface(bond_renderer, surface);
	/* send error */
	SDLERROR(texture);
	SDL_QueryTexture(texture, NULL, NULL, &rec.w, &rec.h);
	SDL_FreeSurface(surface);
	return;
}

const int Texture::GetWidth() const
{
	return rec.w;
}

const int Texture::GetHeight() const
{
	return rec.h;
}

SDL_Texture* Texture::GetTexture()
{
	return texture;
}

/* **************** WordTexture **************** */

WordTexture::WordTexture(SDL_Renderer* renderer)
{
	texture = nullptr;
	bond_renderer = renderer;
	rec.x = rec.y = rec.h = rec.w = 0;
	
	file = DEFAULT_FONT;
	ptsize = 28;
	word = "\0";
	color.r = color.g = color.b = color.a = 0;
	font = nullptr;
	
	return;
}

WordTexture::WordTexture(SDL_Renderer* renderer, std::string contentword)
{
	texture = nullptr;
	bond_renderer = renderer;
	rec.x = rec.y = rec.h = rec.w = 0;
	
	file = DEFAULT_FONT;
	ptsize = 28;
	word = "\0";
	color.r = color.g = color.b = color.a = 0;
	font = nullptr;
	
	Update(file, ptsize, contentword, color);
	
	return;
}

WordTexture::~WordTexture()
{
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
	texture = nullptr;
	return;
}

void WordTexture::Update(std::string fontfile, int pointsize, std::string contentword, SDL_Color wordcolor)
{
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
	texture = nullptr;
	
	if (fontfile != "\0")
		file = fontfile;
	ptsize = pointsize;
	word = contentword;
	color = wordcolor;
	
	font = TTF_OpenFont(file.c_str(), ptsize);
	/* send error */
	TTFERROR(font);
	SDL_Surface* surface = nullptr;
	surface = TTF_RenderText_Solid(font, word.c_str(), color);
	/* send error */
	TTFERROR(surface);
	TTF_CloseFont(font);
	font = nullptr;
	
	texture = SDL_CreateTextureFromSurface(bond_renderer, surface);
	/* send error */
	SDLERROR(texture);
	SDL_FreeSurface(surface);
		
	SDL_QueryTexture(texture, NULL, NULL, &rec.w, &rec.h);
	return;
}

void WordTexture::UpdateFont(std::string fontfile)
{
	Update(fontfile, ptsize, word, color);
	return;
}

void WordTexture::UpdateSize(int pointsize)
{
	Update(file, pointsize, word, color);
	return;
}

void WordTexture::UpdateWord(std::string contentword)
{
	Update(file, ptsize, contentword, color);
	return;
}

void WordTexture::UpdateColor(SDL_Color wordcolor)
{
	Update(file, ptsize, word, wordcolor);
	return;
}

const int WordTexture::GetWidth() const
{
	return rec.w;
}

const int WordTexture::GetHeight() const
{
	return rec.h;
}

SDL_Texture* WordTexture::GetTexture()
{
	return texture;
}
