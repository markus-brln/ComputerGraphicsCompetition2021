#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include "../raytracerandfriends/raytracer.h"
#include "../raytracerandfriends/shapes/sphere.h"


class Controller
{
    Raytracer &d_raytracer;             // all data members with d_...
    sf::RenderWindow &d_window;         // sf::Window == view in MVC pattern

    public:
        Controller() = delete;
        Controller(Raytracer &raytracer, sf::RenderWindow &window);   // 1.cc

        void run();
        void handleEvent(sf::Event &event);
        void handleKeyPresses();

        void configureSolarSystem();
        sf::Text createText();
};



#endif

