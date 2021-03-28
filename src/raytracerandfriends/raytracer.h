#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "scene.h"

#include <string>
//#include <SFML/Graphics/Image.hpp>
#include "../SFML/Graphics.hpp"

// Forward declarations
class Light;
class Material;

#include "json/json_fwd.h"

class Raytracer
{
    

    public:
        Scene scene;        // MB made public to allow high-level access to setEye()

        bool readScene(std::string const &ifname);
        void renderToFile(std::string const &ofname);

        sf::Image renderToSFImage();      // MB returns sf::Image obj

    private:

        bool parseObjectNode(nlohmann::json const &node);

        Light parseLightNode(nlohmann::json const &node) const;
        Material parseMaterialNode(nlohmann::json const &node) const;
};

#endif

