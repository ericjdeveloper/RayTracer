#pragma once


#include "SDL2/SDL.h"
#include "ScreenData.h"

class Renderer {
public:
	virtual void renderWindow(ScreenData* sd) =0;
};