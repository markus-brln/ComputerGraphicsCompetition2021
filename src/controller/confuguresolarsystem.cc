#include "controller.ih"


void Controller::configureSolarSystem()
{
    cout << "Configuring planet sizes and distances...\n";

    // Sun, Mercury, Venus, Earth, Moon (Earth), Mars, Jupiter, Saturn, Uranus, Neptune, Pluto
    // 24 -> 2.400 km
    vector<size_t> planetRadii{ 700, 24, 60, 64, 17, 34, 669, 582, 253, 246, 12 };

    // 58 -> 58 million km
    vector<size_t> planetDistances{ 0, 58, 108, 150, 150, 228, 778, 1434, 2871, 4495, 5906 };

    vector<Sphere*> planets;

    // get all spheres that have a texture -> planet
    for (ObjectPtr &planet : d_raytracer.scene.getObjects())
    {
        cout << planet->isSkybox << ' ';
        //if (!planet->isSkybox && planet->material.hasTexture)
            //planets.push_back(dynamic_cast<Sphere*>(planet));
    }

    //dynamic_cast<Cat*>(AnimalPtr1);
    //cout << d_raytracer.scene.getObjects();
    cout << planets.size()<< '\n';

    for (size_t idx = 0; idx < planets.size(); ++idx)
    {
        //planets[idx]->;
    }    
}