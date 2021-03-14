#include "main.ih"

int main()
{
    Raytracer raytracer;

    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");    // sf::Window is view in MVC pattern
    Controller controller{ raytracer, window };

    controller.run();

    return 0;
}

// TODO: transformations from openGL shaders applied to raytracing
