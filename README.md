# RayTracer
This program is intended to be a realtime raytracer. Currently it's incredibly simple, and so runs quite slowly. However, it is slowly growing.
Currently, this renderer supports 
  - variable camera position
  - various shapes 
    - spheres
    - cubes
    - planes
  - multiple materials
    -metal
    -lambertian
    

### Future Updates:
The intention for this raytracer is to try and create an engine that supports liminal space. This is not an easy task, and it might be a long while before that is
completely implemented. However, all design choices made now will be made with this future behaviour in mind.

## Installation:
Installing this program is fairly simple. The only dependencies are the SDL2 library, which can be found [here](https://www.libsdl.org/download-2.0.php).
There are tons of tutorials online on how to install SDL2 if youre unfamiliar with linking libraries as I was.

Once that's completed, you should be able to hit run, and thats it!


## Credits:
This raytracer was built starting with code/concepts from the following articles:

[Raytracing in a Weekend](https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf):
A really good link for explaining the workings of a ray tracer and how to write up a simple one in c++. It's not the cleanest code, but it works.
This renderer expands on those ideas.

[A Minimal Ray-Tracer](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/parametric-and-implicit-surfaces): Really handy for getting a feel for the math behind ray-tracers. Mostyly pseudocode, but still incredibly useful


