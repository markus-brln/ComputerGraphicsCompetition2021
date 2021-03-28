#include "controller.ih"

Controller::Controller(Raytracer &raytracer, RenderWindow &window)
:
    d_raytracer(raytracer),
    d_window(window)
{
}

