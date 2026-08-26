#pragma once

#include "Renderer.h"
#include "../Vector.h"

//class for handling the output of the render
class SDLWindowRenderer : public Renderer{
public:
	//constructor that sets the width, height, and scale of the window
	SDLWindowRenderer(ScreenData* screen, int scale);
	//function for rendering the window
	void renderWindow(ScreenData* sd);

private:
	//the width, height, and scale variables
	int width, height;
	//the actual SDL window
	SDL_Window *window;
	//the SDL side renderer
	SDL_Renderer *renderer;

	SDL_Texture *renderTexture;
	int pitch;
};

//constructor that initializes the window
SDLWindowRenderer::SDLWindowRenderer(ScreenData* screen, int scale)
{
	//set the width, height, and scale
	height = screen->getHeight();
	width = screen->getWidth();
	
	pitch = screen->getWidth() * 3;
	//SDL window creation
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Raytracer", width * scale, height * scale, 0, &window, &renderer);
	SDL_SetRenderLogicalPresentation(renderer, width,height, SDL_RendererLogicalPresentation::SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);

	renderTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_TARGET, width, height);
	SDL_SetTextureScaleMode(renderTexture, SDL_SCALEMODE_NEAREST);
}

//renders the pixels from the array to the window
void SDLWindowRenderer::renderWindow(ScreenData* sd)
{
	
	SDL_UpdateTexture(renderTexture, NULL, (void **)sd->getPixels(), sd->getWidth() * 3);
	SDL_RenderTextureRotated(renderer, renderTexture, NULL, NULL, 0, NULL,SDL_FlipMode::SDL_FLIP_VERTICAL);

	char fps[4];
	snprintf(fps, 4, "%f", sd->fps);
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDebugText(renderer, 0, 0, fps);

	//render the view to the screen
	SDL_RenderPresent(renderer);


}