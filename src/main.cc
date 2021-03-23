#include "main.ih"

// define globals
int SIZE = 400;
std::string SCENE = "../Scenes/3_refraction/3.json";

// single sphere with earth texture
//std::string SCENE = "../Scenes/5_fixed_texture/1.json";


int main()
{
    // initialize raytracer
    Raytracer raytracer;

    sf::RenderWindow window(sf::VideoMode(SIZE, SIZE), "SFML works!");    // sf::Window is view in MVC pattern
    Controller controller{ raytracer, window };

    controller.run();

    return 0;
}

// TODO: transformations from openGL shaders applied to raytracing
