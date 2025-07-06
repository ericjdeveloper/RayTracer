#pragma once


#include "SDL3/SDL.h"
#include "../ScreenData.h"
#include "../Vector.h"

class Renderer {
public:
	virtual void renderWindow(ScreenData* sd) =0;
};

