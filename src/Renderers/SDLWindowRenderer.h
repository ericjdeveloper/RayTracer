#pragma once

#include "Renderer.h"
#include "../Vector.h"

//class for handling the output of the render
class SDLWindowRenderer : public Renderer{
public:
	//constructor that sets the width, height, and scale of the window
	SDLWindowRenderer(int w, int h);
	//function for rendering the window
	void renderWindow(ScreenData* sd);

private:
	//the width, height, and scale variables
	int width, height;
	//the actual SDL window
	SDL_Window *window;
	//the SDL side renderer
	SDL_Renderer *renderer;

};

//constructor that initializes the window
SDLWindowRenderer::SDLWindowRenderer(int w, int h)
{
	//set the width, height, and scale
	width = w;
	height = h;

	//SDL window creation
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Raytracer", w, h, 0, &window, &renderer);

}

//renders the pixels from the array to the window
void SDLWindowRenderer::renderWindow(ScreenData* sd)
{
	
	float scale_x = (float)sd->getWidth() / width;
	float scale_y = (float)sd->getHeight() / height;

	

	//loop through the width
	for (int x =0; x < width; x++)
	{
		//loop through the height
		for (int y=0; y < height; y++) {

			int screen_x = floor(x * scale_x);
			int screen_y = floor(y * scale_y);


			//get the rgb values from the array 
			Uint8 r;
			Uint8 g;
			Uint8 b;

			sd->getPixel(screen_x, screen_y, r, g, b);
			//set the render color
			SDL_SetRenderDrawColor(renderer, r, g, b, 1);


			//draw the current pixel with the color described
			SDL_RenderPoint(renderer, x, height-y);

		}
	}

	//render the view to the screen
	SDL_RenderPresent(renderer);
}