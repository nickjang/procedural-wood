#ifndef DISPLAY_INCLUDED_H
#define DISPLAY_INCLUDED_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
	SDL_Rect draw_rect;    // dimensions of button
	struct {
		Uint8 r, g, b, a;
	} colour;
} button;


class Display
{
public:
	Display(int width, int height, const std::string& title);

	void Clear(float r, float g, float b, float a);
	void SwapBuffers();
	int handleEvent(SDL_Event& e);

	virtual ~Display();
protected:
private:
	void operator=(const Display& display) {}
	Display(const Display& display) {}

	SDL_Window* m_window;
	SDL_Window* m_window2;
	SDL_GLContext m_glContext;
	SDL_Renderer* m_renderer;
	button bbowl;
	button bspoon;
	button bbox;
	button bsphere;
	TTF_Font* m_Sans;
	SDL_Color m_White;
	SDL_Surface* m_sbowl;
	SDL_Surface* m_sspoon;
	SDL_Surface* m_sbox;
	SDL_Surface* m_ssphere;
	SDL_Texture* m_tbowl;
	SDL_Texture* m_tspoon;
	SDL_Texture* m_tbox;
	SDL_Texture* m_tsphere;
};

#endif