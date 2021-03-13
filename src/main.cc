#include "raytracerandfriends/raytracer.h"
#include <SFML/Graphics.hpp>
#include <omp.h>

int main()
{
    Raytracer raytracer;

    // read the scene
    if (!raytracer.readScene("Scenes/3_refraction/1.json"))
    {
        cerr << "Error: reading scene from " << 
            " failed - no output generated.\n";
        return 1;
    }

    sf::Clock Clock;                // for frame rate
    sf::Image img = raytracer.renderToSFImage();
    sf::Texture texture;
    texture.loadFromImage(img);  //Load Texture from image
    sf::Sprite sprite;
    sprite.setTexture(texture);   



    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Image img = raytracer.renderToSFImage();
        sf::Texture texture;
        texture.loadFromImage(img);  //Load Texture from image
        sf::Sprite sprite;
        sprite.setTexture(texture);  

        cout << "framerate: " <<  1000.0 / Clock.getElapsedTime().asMilliseconds() << '\n';
        Clock.restart();

        window.clear();
        window.draw(shape);
        window.draw(sprite);
        window.display();
    }

    return 0;
}