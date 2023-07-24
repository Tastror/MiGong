#ifndef _SDLQuickLoad_H_
#define _SDLQuickLoad_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <cstring>
#include <iostream>

class Window {
private:
	const char* const Title;
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	const int GetWidth() const;
	const int GetHeight() const;
	SDL_Renderer* GetRenderer();
	SDL_Renderer* gr();
	void Clear();
	void Present();
public:
	Window(const std::string& Title, const int& Width, const int& Height);
	~Window();
};

class Texture {
protected:
	SDL_Texture* texture;
	SDL_Renderer* bond_renderer;
	SDL_Rect rec;
public:
	const int GetWidth() const;
	const int GetHeight() const;
	SDL_Texture* GetTexture();
public:
	void Load(const std::string& file);
	void LoadParent(const std::string& file, const SDL_Color& color = { 255, 255, 255, 0 });
public:
	Texture(SDL_Renderer* renderer);
	~Texture();
};
 
class WordTexture {
protected:
	SDL_Texture* texture;
	SDL_Renderer* bond_renderer;
	SDL_Rect rec;
	std::string file;
	int ptsize;
	std::string word;
	SDL_Color color;
	TTF_Font* font;
public:
	const int GetWidth() const;
	const int GetHeight() const;
	SDL_Texture* GetTexture();
public:
	void Update(std::string fontfile, int pointsize, std::string contentword, SDL_Color wordcolor = { 0, 0, 0, 0 });
	void UpdateFont(std::string fontfile);
	void UpdateSize(int pointsize);
	void UpdateWord(std::string contentword);
	void UpdateColor(SDL_Color wordcolor);
public:
	WordTexture(SDL_Renderer* renderer);
	WordTexture(SDL_Renderer* renderer, std::string contentword);
	~WordTexture();
};

#endif
