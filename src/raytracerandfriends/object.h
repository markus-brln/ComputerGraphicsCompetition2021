#ifndef OBJECT_H_
#define OBJECT_H_

#include "material.h"

// not really needed here, but deriving classes may need them
#include "hit.h"
#include "ray.h"
#include "triple.h"

#include <memory>
//#include <string>

class Object;
typedef std::shared_ptr<Object> ObjectPtr;

class Object
{
    public:
        Material material;
        bool isSkybox = false;                      // MB skybox won't experience
                                                    // raytracing, only getting color at pixel
                                                    // to reduce computational complexity
        //std::string objType;                        // MB 

        //Point planetPosition;                       // MB specifically for planets
        //size_t planetRadius;

        virtual ~Object() = default;

        virtual Hit intersect(Ray const &ray) = 0;  // must be implemented
                                                    // in derived class

        virtual Vector toUV(Point const &hit)
        {
            // bogus implementation
            return Vector{};
        }

        virtual void checkCorrectEye(Point &eye) = 0;   // every derived class must 
                                                        // have this check
};

#endif
