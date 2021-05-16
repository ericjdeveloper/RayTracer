#pragma once

class ScreenData {
public:

	ScreenData(int width, int height);
	//function to set pixel (x,y) to value (r,g,b)
	void setPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b);
	//function for getting the pixel (x,y) into (r,g,b)
	void getPixel(int x, int y, Uint8& r, Uint8& g, Uint8& b);

	//gets the pixel width of the window
	int getWidth() { return width; }
	//gets the pixel height of the window
	int getHeight() { return height; }
private:

	int width, height;
	
	Uint8* pixels;
};

