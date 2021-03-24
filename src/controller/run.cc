#include "controller.ih"
#include "../utils/utils.h"

void Controller::run()
{
    // read the scene
    if (!d_raytracer.readScene(SCENE))
    {
        cerr << "Error: reading scene from " << 
            " failed - no output generated.\n";
        return;
    }

    sf::Clock Clock;                // for frame rate
    sf::Event event;
    sf::Image img;
    sf::Texture texture;
    sf::Sprite sprite;

    while (d_window.isOpen())
    {
        while (d_window.pollEvent(event))
            handleEvent(event);     // closing, reset
        
        handleKeyPresses();         // live input
        
        img = d_raytracer.renderToSFImage();
        //std::cout << "hoi";
        //upscaleSFImage(img);        // utils
        //auto start = Clock.getElapsedTime().asMilliseconds();
        texture.loadFromImage(img);  //Load Texture from image
        sprite.setTexture(texture);
        
        cout << "framerate: " <<  1000.0 / Clock.getElapsedTime().asMilliseconds() << '\n';
        //cout << "time: " << Clock.getElapsedTime().asMilliseconds() - start << '\n';
        
        Clock.restart();
        //d_window.clear();     // not sure whether this is needed, probably not
                                // since whole screen is refreshed
        d_window.draw(sprite);
        d_window.display();
        
    }
}
