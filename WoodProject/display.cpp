#include "display.h"
#include <GL/glew.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>


bool XYInRect(const SDL_Rect& rect, int x, int y)
{
	return ((x >= rect.x && x <= rect.x + rect.w) && (y >= rect.y && y <= rect.y + rect.h));
}


Display::Display(int width, int height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	if (TTF_Init() != 0)
		std::cerr << "TTF not intialized" << std::endl;

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");


	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);
	m_window2 = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 700, SDL_WINDOW_RESIZABLE);

	m_renderer = NULL;
	m_renderer = SDL_CreateRenderer(m_window2, -1, SDL_RENDERER_ACCELERATED);
	if (!m_renderer) {   // renderer creation may fail too
		fprintf(stderr, "create renderer failed: %s\n", SDL_GetError());
		return;
	}

	bbowl.colour = { 230, 200, 250, 255 };
	bbowl.draw_rect = { 0, 0, 700, 175 };
	bspoon.colour = { 250, 230, 200, 255 };
	bspoon.draw_rect = { 0, 175, 700, 175 };
	bbox.colour = { 200, 250, 230, 255 };
	bbox.draw_rect = { 0, 350, 700, 175 };
	bsphere.colour = { 200, 230, 250, 255 };
	bsphere.draw_rect = { 0, 525, 700, 175 };

	m_Sans = TTF_OpenFont("./misc/fonts/DroidSans.ttf", 100);
	m_White = { 255, 255, 255 };
	m_sbowl = TTF_RenderText_Solid(m_Sans, "Bowl", m_White);
	m_sspoon = TTF_RenderText_Solid(m_Sans, "Spoon", m_White);
	m_sbox = TTF_RenderText_Solid(m_Sans, "Box", m_White);
	m_ssphere = TTF_RenderText_Solid(m_Sans, "Sphere", m_White);
	m_tbowl = SDL_CreateTextureFromSurface(m_renderer, m_sbowl);
	m_tspoon = SDL_CreateTextureFromSurface(m_renderer, m_sspoon);
	m_tbox = SDL_CreateTextureFromSurface(m_renderer, m_sbox);
	m_tsphere = SDL_CreateTextureFromSurface(m_renderer, m_ssphere);


	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize!" << std::endl;
	}
	if (GL_TRUE != glewGetExtension("GL_EXT_texture3D"))
	{
		std::cerr << "3D texture is not supported !" << std::endl;
	}

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

Display::~Display()
{
	SDL_DestroyTexture(m_tbowl);
	SDL_DestroyTexture(m_tspoon);
	SDL_DestroyTexture(m_tbox);
	SDL_DestroyTexture(m_tsphere);
	SDL_FreeSurface(m_sbowl);
	SDL_FreeSurface(m_sspoon);
	SDL_FreeSurface(m_sbox);
	SDL_FreeSurface(m_ssphere);
	TTF_CloseFont(m_Sans);
	SDL_DestroyRenderer(m_renderer);
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_DestroyWindow(m_window2);
	TTF_Quit();
	SDL_Quit();
}

void Display::Clear(float r, float g, float b, float a)
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Display::SwapBuffers()
{
	SDL_SetRenderDrawColor(m_renderer, bbowl.colour.r, bbowl.colour.g, bbowl.colour.b, bbowl.colour.a);
	SDL_RenderFillRect(m_renderer, &bbowl.draw_rect);
	SDL_SetRenderDrawColor(m_renderer, bspoon.colour.r, bspoon.colour.g, bspoon.colour.b, bspoon.colour.a);
	SDL_RenderFillRect(m_renderer, &bspoon.draw_rect);
	SDL_SetRenderDrawColor(m_renderer, bbox.colour.r, bbox.colour.g, bbox.colour.b, bbox.colour.a);
	SDL_RenderFillRect(m_renderer, &bbox.draw_rect);
	SDL_SetRenderDrawColor(m_renderer, bsphere.colour.r, bsphere.colour.g, bsphere.colour.b, bsphere.colour.a);
	SDL_RenderFillRect(m_renderer, &bsphere.draw_rect);

	SDL_RenderCopy(m_renderer, m_tbowl, NULL, &bbowl.draw_rect);
	SDL_RenderCopy(m_renderer, m_tspoon, NULL, &bspoon.draw_rect);
	SDL_RenderCopy(m_renderer, m_tbox, NULL, &bbox.draw_rect);
	SDL_RenderCopy(m_renderer, m_tsphere, NULL, &bsphere.draw_rect);
	SDL_RenderPresent(m_renderer);


	SDL_GL_SwapWindow(m_window);
	

}

int Display::handleEvent(SDL_Event& e)
{
	//If an event was detected for this window
	if (e.window.windowID == SDL_GetWindowID(m_window2))
	{
		//Caption update flag
		switch (e.type)
		{
		case SDL_MOUSEBUTTONUP:
			if (XYInRect(bbowl.draw_rect, e.button.x, e.button.y))
				return 1;
			else if (XYInRect(bspoon.draw_rect, e.button.x, e.button.y))
				return 2;
			else if (XYInRect(bbox.draw_rect, e.button.x, e.button.y))
				return 3;
			else if (XYInRect(bsphere.draw_rect, e.button.x, e.button.y))
				return 4;
			break;
		}
	}
	return NULL;
}