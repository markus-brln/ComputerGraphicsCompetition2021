#include "main.ih"

// define globals
int SIZE = 300;
bool SolarSystemSimOn = false;          // at start no planet movement, press Space to start
std::string SCENE = "../Scenes/myScenes/7solarSystem.json";
//std::string SCENE = "../Scenes/myScenes/8fancy.json";
//std::string SCENE = "../Scenes/myScenes/5.1earthAloneRotation.json";



int main()
{
    Raytracer raytracer;
    sf::RenderWindow window(sf::VideoMode(SIZE, SIZE), "Raytracing");    // sf::Window is view in MVC pattern
    
    
    Controller controller{ raytracer, window };
    
    if (!raytracer.readScene(SCENE))
    {
        cerr << "Error: reading scene from " << 
            " failed - no output generated.\n";
        exit(-1);
    }
    controller.run();

    return 0;
}

// TODO: transformations from openGL shaders applied to raytracing
