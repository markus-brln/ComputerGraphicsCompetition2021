#include "main.ih"

// define globals
int SIZE = 300;
bool SolarSystemSimOn = false;          // at start no planet movement, press Space to start
std::string SCENE = string{};           // a global needs to be defined




int main()
{
    chooseScene();                      // utils.cc

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
