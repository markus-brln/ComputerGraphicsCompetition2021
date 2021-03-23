#include "main.ih"

// define globals
int SIZE = 400;
std::string SCENE = "../Scenes/myScenes/3mixed.json";


int main()
{
    // initialize raytracer
    Raytracer raytracer;

    sf::RenderWindow window(sf::VideoMode(SIZE, SIZE), "SFML window");    // sf::Window is view in MVC pattern
    Controller controller{ raytracer, window };

    controller.run();

    return 0;
}

// TODO: transformations from openGL shaders applied to raytracing
