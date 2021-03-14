#include "controller.ih"


void Controller::handleEvent(Event &event)
{
    if (event.type == sf::Event::Closed)
        d_window.close();
    if (event.type == sf::Event::EventType::KeyPressed)
    {
        switch (event.key.code)
        {
        case (sf::Keyboard::W):                     // forward / backward
            d_raytracer.scene.getEye().z -= 30;
            break;
        case (sf::Keyboard::S):
            d_raytracer.scene.getEye().z += 30;
            break;
        case (sf::Keyboard::A):
            d_raytracer.scene.getEye().x -= 30;     // sideways
            break;
        case (sf::Keyboard::D):
            d_raytracer.scene.getEye().x += 30;
            break;
        case (sf::Keyboard::Q):
            d_raytracer.scene.getEye().y += 30;      // up / down
            break;
        case (sf::Keyboard::E):
            d_raytracer.scene.getEye().y -= 30;
            break;
        default:
            break;
        }
    }
}