#include "main.ih"

// define globals
int SIZE = 300;
//int UPSCALED = 2 * SIZE;
std::string SCENE = "../Scenes/myScenes/7solarSystem.json";
//std::string SCENE = "../Scenes/myScenes/5.1earthAloneRotation.json";



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
