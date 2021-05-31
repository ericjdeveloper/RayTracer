# RayTracer
This program is intended to be a realtime raytracer. Currently it's incredibly simple, and so runs quite slowly. However, it is slowly growing.
Currently, this renderer supports 
  - variable camera position/rotation
  - various shapes with unique sizes/rotations/positions
    - spheres
    - cubes
    - planes
  - multiple materials
    - metal
    - lambertian
    

### Future Updates:
The intention for this raytracer is to try and create an engine that supports liminal space. This is not an easy task, and it might be a long while before that is
completely implemented. However, all design choices made now will be made with this future behaviour in mind.

## Installation:
Installing this program is fairly simple. The only dependencies are the SDL2 library, which can be found [here](https://www.libsdl.org/download-2.0.php).
I used visual studio code, but other programs will require different methods for including this library.

to build, you'll need to compile the c program. It will vary based on your file paths, but here's an example build call:

`g++.exe -g \src\Main.cpp -o \build\Raytracer.exe -I\src -I[PATH_TO_SDL_INCLUDE] -L[PATH_TO_SDL_LIB] -lmingw32 -lSDL2main -lSDL2 -mwindows`

running is as easy as going to the build folder and clicking on the .exe (make sure that the SDL2.dll is present)


## Credits:
This raytracer was built starting with code/concepts from the following articles:

[Raytracing in a Weekend](https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf):
A really good link for explaining the workings of a ray tracer and how to write up a simple one in c++. It's not the cleanest code, but it works.
This renderer expands on those ideas.

[A Minimal Ray-Tracer](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/parametric-and-implicit-surfaces): Really handy for getting a feel for the math behind ray-tracers. Mostly pseudocode, but still incredibly useful


