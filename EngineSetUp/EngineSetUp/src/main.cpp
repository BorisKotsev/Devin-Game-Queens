#include "Presenter.h"

#undef main

int main(int* argc, char* argv[])
{
	Presenter presenter;
	
	presenter.init();
	
	Drawable drawable;

	drawable.rect = { 0, 0, 100, 100 };
	drawable.texture = LoadTexture("player.bmp", presenter.m_main_renderer);

	while (1)
	{
		drawObject(drawable);
		presenter.draw();
	}
	
	SDL_Delay(10000);
	
	return 0;
}