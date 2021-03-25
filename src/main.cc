#include "main.ih"

// define globals
int SIZE = 300;
bool SolarSystemSimOn = false;          // at start no planet movement, press Space to start

// try out different scenes
//std::string SCENE = "../Scenes/myScenes/7solarSystem.json";
//std::string SCENE = "../Scenes/myScenes/8fancy.json";
//std::string SCENE = "../Scenes/myScenes/5earthAloneRotation.json";
std::string SCENE = "../Scenes/myScenes/3mixed.json";


int main()
{
    chooseScene();

    Raytracer raytracer;                // raytracer+scene are "model" in MVC pattern
    sf::RenderWindow window(            // sf::Window is view 
        sf::VideoMode(SIZE, SIZE), "Raytracing"
    );    
    window.setFramerateLimit(30);       // in case someone has a Threadripper CPU...

                                        // controller draws on window, changes model
    Controller controller{ raytracer, window };
    
    if (!raytracer.readScene(SCENE))
    {
        cerr << "Error: reading scene from " << 
            " failed - no output generated.\n";
        exit(-1);
    }
    controller.run();                   // start the game loop

    return 0;
}

// TODO: transformations from openGL shaders applied to raytracing
