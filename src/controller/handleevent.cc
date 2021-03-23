#include "controller.ih"


void Controller::handleEvent(Event &event)
{
    if (event.type == sf::Event::Closed)
        d_window.close();
    if (event.type == sf::Event::EventType::KeyPressed)
    {
        switch (event.key.code)
        {
        // Control Eye Position
        case (sf::Keyboard::W):                     // forward / backward
            //d_raytracer.scene.getEye().z -= 30;
            d_raytracer.scene.translateEye(0, 0, -30);
            break;
        case (sf::Keyboard::S):
            //d_raytracer.scene.getEye().z += 30;
            d_raytracer.scene.translateEye(0, 0, 30);
            break;
        case (sf::Keyboard::A):
            //d_raytracer.scene.getEye().x -= 30;     // sideways
            d_raytracer.scene.translateEye(-30, 0, 0);
            break;
        case (sf::Keyboard::D):
            //d_raytracer.scene.getEye().x += 30;
            d_raytracer.scene.translateEye(30, 0, 0);
            break;
        case (sf::Keyboard::Q):
            //d_raytracer.scene.getEye().y += 30;     // up / down
            d_raytracer.scene.translateEye(0, 30, 0);
            break;
        case (sf::Keyboard::E):
            //d_raytracer.scene.getEye().y -= 30;
            d_raytracer.scene.translateEye(0, -30, 0);
            break;

        // Control Eye Rotation
        case (sf::Keyboard::Up):                    // look up
            d_raytracer.scene.getEyeRotation().x += 0.05;
            break;
        case (sf::Keyboard::Down):                  // look down
            d_raytracer.scene.getEyeRotation().x -= 0.05;
            break;
        case (sf::Keyboard::Left):                  // look left
            d_raytracer.scene.getEyeRotation().y += 0.05;
            break;
        case (sf::Keyboard::Right):                 // look right
            d_raytracer.scene.getEyeRotation().y -= 0.05;
            break;
        case (sf::Keyboard::Numpad1):                  // rotate left
            d_raytracer.scene.getEyeRotation().z -= 0.05;
            break;
        case (sf::Keyboard::Numpad3):                  // rotate right
            d_raytracer.scene.getEyeRotation().z += 0.05;
            break;

        // Reset
        case (sf::Keyboard::Backspace):                  // rotate right
            d_raytracer.scene.getEye() = Vector{};
            d_raytracer.scene.getEyeRotation() = Vector{};
            break;

        default:
            break;
        }
    }
}