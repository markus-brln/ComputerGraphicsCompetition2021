#include "controller.ih"


void Controller::handleKeyPresses()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        d_raytracer.scene.translateEye(0, 0, -30);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        d_raytracer.scene.translateEye(0, 0, 30);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        d_raytracer.scene.translateEye(-30, 0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        d_raytracer.scene.translateEye(30, 0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        d_raytracer.scene.translateEye(0, 30, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        d_raytracer.scene.translateEye(0, -30, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        d_raytracer.scene.getEyeRotation().x += 0.05;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        d_raytracer.scene.getEyeRotation().x -= 0.05;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        d_raytracer.scene.getEyeRotation().y += 0.05;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        d_raytracer.scene.getEyeRotation().y -= 0.05;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
        d_raytracer.scene.getEyeRotation().z -= 0.05;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
        d_raytracer.scene.getEyeRotation().z += 0.05;
}
// this is for live input (allowing for multiple input actions at the same time),
// nice tutorial about it: https://www.youtube.com/watch?v=hZ2WogmdLPo&t=76s