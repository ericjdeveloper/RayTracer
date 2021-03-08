#pragma once

#include "SDL2/SDL.h"
#include "vec3.h"

//class for handling the output of the render
class WindowHandler {
public:
	//constructor that sets the width, height, and scale of the window
	WindowHandler(int w, int h, int s);
	//function for rendering the window
	void renderWindow();
	//function to set pixel (x,y) to value (r,g,b)
	void setPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b);
	//function for getting the pixel (x,y) into (r,g,b)
	void getPixel(int x, int y, Uint8& r, Uint8& g, Uint8& b);


	//gets the pixel width of the window
	int getWidth() { return width; }
	//gets the pixel height of the window
	int getHeight() { return height; }

private:
	//the width, height, and scale variables
	int width, height, scale;
	//the actual SDL window
	SDL_Window *window;
	//the SDL side renderer
	SDL_Renderer *renderer;

	//array for storing the pixel values
	//note, its a 1D array (with every 3 values representing the r, g ,b respectively)
	//the array stores by x then y
	Uint8 *pixels;
};

//constructor that initializes the window
WindowHandler::WindowHandler(int w, int h, int s)
{
	//set the width, height, and scale
	width = w;
	height = h;
	scale = s;
	//initialize the pixel array
	pixels = new Uint8[width * height * 3];

	//SDL window creation
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Raytracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w * scale, h * scale, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);

}

//renders the pixels from the array to the window
void WindowHandler::renderWindow()
{
	
	//loop through the width
	for (int x =0; x < width; x++)
	{
		//loop through the height
		for (int y=0; y < height; y++) {

			//get the rgb values from the array 
			Uint8 r;
			Uint8 g;
			Uint8 b;

			getPixel(x, y, r, g, b);
			
			//set the render color
			SDL_SetRenderDrawColor(renderer, r, g, b, 1);

			//loop through the scaling offset
			for (int i = 0; i < scale; i++)
			{
				for (int j = 0; j < scale; j++)
				{
					//draw the current pixel with the color described
					SDL_RenderDrawPoint(renderer, (x * scale) + i, ((height -y) * scale) + j);
				}
			}
		}
	}

	//render the view to the screen
	SDL_RenderPresent(renderer);
}

//sets the given pixel value (x,y) to (r,g,b)
void WindowHandler::setPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b) {

	//get the index value for the array
	int index = ((y * width) + x) * 3;

	//set the respective values

	
	pixels[index] = r;
	pixels[index + 1] = g;
	pixels[index + 2] = b;
	
}


//gets the given pixel (x,y) into (r,g,b)
void WindowHandler::getPixel(int x, int y, Uint8& r, Uint8& g, Uint8& b)
{
	//get the index value for the pixel
	int index = ((y * width) + x) * 3;

	//store the values into r,g,b
	r = pixels[index];
	g = pixels[index + 1];
	b = pixels[index + 2];
}