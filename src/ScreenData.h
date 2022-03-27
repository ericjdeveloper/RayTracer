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

ScreenData::ScreenData(int w, int h)
{
	width = w;
	height = h;

	pixels = new Uint8[width * height * 3];
}

//sets the given pixel value (x,y) to (r,g,b)
void ScreenData::setPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b) {

	//get the index value for the array
	int index = ((y * width) + x) * 3;

	//set the respective values


	pixels[index] = r;
	pixels[index + 1] = g;
	pixels[index + 2] = b;

}


//gets the given pixel (x,y) into (r,g,b)
void ScreenData::getPixel(int x, int y, Uint8& r, Uint8& g, Uint8& b)
{
	//get the index value for the pixel
	int index = ((y * width) + x) * 3;

	//store the values into r,g,b
	r = pixels[index];
	g = pixels[index + 1];
	b = pixels[index + 2];
}

