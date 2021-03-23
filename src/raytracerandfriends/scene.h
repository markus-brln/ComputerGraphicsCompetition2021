#ifndef SCENE_H_
#define SCENE_H_

#include "light.h"
#include "object.h"
#include "triple.h"

#include <vector>
#include <utility>
#include <iostream>

#include <SFML/Graphics/Image.hpp>     // if you have SFML installed


using namespace std; 

// Forward declarations
class Ray;
class Image;

class Scene
{
    std::vector<ObjectPtr> objects;
    std::vector<LightPtr> lights;
    Point eye;
    Vector eyeRotation;                 // MB 

    bool renderShadows;
    unsigned recursionDepth;
    unsigned supersamplingFactor;

    // Offset multiplier. Before casting a new ray from a hit point,
    // move the hit point in the direction of the normal with this offset
    // to prevent finding an intersection with the same object due to
    // floating point inaccuracies. This prevents shadow acne, among other problems.
    double const epsilon = 1E-3;

    public:
        Scene();

        // determine closest hit (if any)
        std::pair<ObjectPtr, Hit> castRay(Ray const &ray) const;

        // trace a ray into the scene and return the color
        Color trace(Ray const &ray, unsigned depth);

        // render the scene to the given image
        void render(Image &img);
        void renderToSFImage(sf::Image &img); // MB


        void addObject(ObjectPtr obj);
        void addLight(Light const &light);
        void setEye(Triple const &position);
        void setEyeRotation(Triple const &rotation);

        Triple &getEye()
        {
            return eye;
        }
        Triple &getEyeRotation()
        {
            return eyeRotation;
        }
        // MB returning references to the eye position&rotation
        // such that the controller can change them
        
        void setRenderShadows(bool renderShadows);
        void setRecursionDepth(unsigned depth);
        void setSuperSample(unsigned factor);

        unsigned getNumObject();
        unsigned getNumLights();
    
    private:
        bool lightObstructed(LightPtr const &light, Point const &hit, Vector const &normalFromObj);
};

#endif
