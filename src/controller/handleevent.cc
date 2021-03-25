#include "controller.ih"


void Controller::handleEvent(Event &event)
{
    if (event.type == sf::Event::Closed)
        d_window.close();

    if (event.type == sf::Event::EventType::KeyPressed)
    {
        switch (event.key.code)
        {
        // Reset
        //case (sf::Keyboard::Backspace):
        //    d_raytracer.scene.getEye() = Vector{ 0, 0, 2000 };
        //    d_raytracer.scene.getEyeRotation() = Vector{ 0, 0, 0 };
        //    break;
        
        case (sf::Keyboard::Space):                 
            SolarSystemSimOn = !SolarSystemSimOn;   // switch bool
            break;

        default:
            break;
        }
    }
}
// for closing and reset, events that should just happen once -> not live input