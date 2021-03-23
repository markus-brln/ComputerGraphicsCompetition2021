#include "controller.ih"
#include "../globals.h"

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


    while (d_window.isOpen())
    {
        sf::Event event;
        while (d_window.pollEvent(event))
            handleEvent(event);
        
        handleKeyPresses();

        sf::Image img = d_raytracer.renderToSFImage();
        sf::Texture texture;
        texture.loadFromImage(img);  //Load Texture from image
        sf::Sprite sprite;
        sprite.setTexture(texture);  
        //cout << "rotation: " << d_raytracer.scene.getEyeRotation() << '\n';
        
        cout << "framerate: " <<  1000.0 / Clock.getElapsedTime().asMilliseconds() << '\n';
        Clock.restart();

        d_window.clear();
        d_window.draw(sprite);
        d_window.display();
    }
}
