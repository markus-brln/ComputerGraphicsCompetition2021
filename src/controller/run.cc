#include "controller.ih"
#include "../utils/utils.h"

void Controller::run()
{
    sf::Clock Clock;                    // for frame rate
    sf::Event event;
    sf::Image img;                      // image of which the pixels are set 
                                        // through raytracing
    sf::Texture texture;                // Texture made from Image
    sf::Sprite sprite;                  // Sprite whose Texture is set

    sf::Text text;                      // for displaying fps
    sf::Font font;
    font.loadFromFile("../fonts/jackInputMonospace.TTF");
    text.setFont(font);
    text.setCharacterSize(10);
    text.setFillColor(sf::Color::White);

    while (d_window.isOpen())
    {
        while (d_window.pollEvent(event))
            handleEvent(event);         // closing, reset
        
        handleKeyPresses();             // live input

                                        // specifically for planets orbiting
        if (SolarSystemSimOn && SCENE == "../Scenes/myScenes/9solarSystem.json")
            d_raytracer.scene.SolarSystemSimStep();
        
        img = d_raytracer.renderToSFImage();    // heavy work
        
        texture.loadFromImage(img);     //Load Texture from image
        sprite.setTexture(texture);
        
        text.setString("fps: " + to_string(1000 / Clock.getElapsedTime().asMilliseconds()));
        
        Clock.restart();
        //d_window.clear();             // not sure whether this is needed, probably not
                                        // since whole screen is refreshed
        d_window.draw(sprite);
        d_window.draw(text);
        d_window.display();
        
    }
}


