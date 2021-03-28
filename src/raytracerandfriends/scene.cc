#include "scene.h"
#include "../utils/utils.h"             // globals and some functions
#include "hit.h"
#include "image.h"
#include "material.h"
#include "ray.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <omp.h>

using namespace std;

pair<ObjectPtr, Hit> Scene::castRay(Ray const &ray) const
{
    // Find hit object and distance
    Hit min_hit(numeric_limits<double>::infinity(), Vector());
    ObjectPtr obj = nullptr;
    for (unsigned idx = 0; idx != objects.size(); ++idx)
    {
        Hit hit(objects[idx]->intersect(ray));
        if (hit.t < min_hit.t)
        {
            min_hit = hit;
            obj = objects[idx];
        }
    }

    return pair<ObjectPtr, Hit>(obj, min_hit);
}
// provided in CG course, find hit with object, if any


bool Scene::lightObstructed(LightPtr const &light, Point const &hit, Vector const &normalFromObj)
{
                                        // from the hitpoint + some N dir to view
    Point hoveringHit = hit + epsilon * normalFromObj;
    Ray shadowRay = Ray{ hoveringHit, light->position - hoveringHit};
    pair<ObjectPtr, Hit> mainhit = castRay(shadowRay);
    
    
    if (!mainhit.first)                 // first == object pointer, nullptr if no hit
        return false;                   // No hit? No obstruction.

    if (mainhit.first->objComment == "Sun") // light not obstructed by Sun's sphere!
        return false;

    Point objHitPoint = shadowRay.O + mainhit.second.t * shadowRay.D;
    if (distance3D(light->position, hoveringHit) < distance3D(objHitPoint, hoveringHit))
        return false;
    
    return true;
}
// look whether the light source is obstructed from its origin to the point
// where it would hit the object


Color Scene::trace(Ray const &ray, unsigned depth)
{
    pair<ObjectPtr, Hit> mainhit = castRay(ray);
    ObjectPtr obj = mainhit.first;
    Hit min_hit = mainhit.second;


    // No hit? Return background color.
    if (!obj)
    {
        return Color(0.0, 0.0, 0.0);
    }

    Material const &material = obj->material;
    Point hit = ray.at(min_hit.t);
    Vector V = -ray.D;

    // Pre-condition: For closed objects, N points outwards.
    Vector N = min_hit.N;

    // The shading normal always points in the direction of the view,
    // as required by the Phong illumination model.
    Vector shadingN;
    if (N.dot(V) >= 0.0)
        shadingN = N;
    else
        shadingN = -N;

    // -------- Texture mapping code
    Color matColor;
    if (material.hasTexture) {
        Vector uvVector = obj->toUV(hit);
        matColor = material.texture.colorAt(uvVector.x, 1.0 - uvVector.y);
        if (obj->isSkybox)                  // MB stop reflection etc if the 
            return matColor;                // object is part of the skybox 
                                            // as determined in json under "comment": "Skybox..."
    } else {
        matColor = material.color;
    }
    //-----------

    // Add ambient once, regardless of the number of lights.
    Color color = material.ka * matColor;

    // Add diffuse and specular components.
    for (auto const &light : lights)
    {
        // OUR CODE BEGIN
        if (renderShadows && lightObstructed(light, hit, shadingN))                  
            continue;
        // OUR CODE END

        Vector L = (light->position - hit).normalized();

        // Add diffuse.
        double dotNormal = shadingN.dot(L);
        double diffuse = std::max(dotNormal, 0.0);
        color += diffuse * material.kd * light->color * matColor;

        // Add specular.
        if(dotNormal > 0)
        {
            Vector reflectDir = reflect(-L, shadingN); // Note: reflect(..) is not given in the framework.
            double specAngle = std::max(reflectDir.dot(V), 0.0);
            double specular = std::pow(specAngle, material.n);

            color += specular * material.ks * light->color;
        }
    }

    if (depth > 0 and material.isTransparent)
    {
        // OUR CODE BEGIN

        // The object is transparent, and thus refracts and reflects light.
        // Use Schlick's approximation to determine the ratio between the two.
        double n_i = 1.0;           // refractive idx outside obj (like air)
        double n_t = material.nt;   // refractive index of obj

        if (N.dot(V) < 0.0)         // light ray is exiting the obj
            swap(n_i, n_t);         // from obj -> air!


        // REFLECTION
                                    // normal procedure like for opaque obj
        Vector reflDir = reflect(ray.D, shadingN);
        Ray reflectRay { hit + epsilon * shadingN, reflDir }; 


        // REFRACTION
        // see slide 71
        Vector part1 = (n_i * (ray.D - ray.D.dot(shadingN) * shadingN) / n_t);
        double underSqrt = 1 - (
            pow(n_i, 2) * (
                1 - pow(ray.D.dot(shadingN), 2)
            ) / pow(n_t, 2)
        );

        Vector part2 = shadingN * sqrt(underSqrt);
        Vector refrDir = part1 - part2;     // vector T on slide 71
                            
                            // "-" other dir because to the inside!!
        Ray refractRay { hit - epsilon * shadingN, refrDir };
        

        // RATIO REFLECTED/REFRACTED

        double k_r;                     // intensity multiplier of reflected ray
        double k_t;                     // ~ of transmitted (refracted) ray          
        
        if (underSqrt < 0 && N.dot(V) < 0.0)// total *internal* reflection, slide 71
        {
            k_r = 1;                        // slide  76
            k_t = 0;
        }
        else
        {
            double k_r0 = pow((n_i-n_t)/(n_i+n_t), 2);  // slide 76
            double phi = angle(-ray.D, shadingN);   // between light and normal on obj

                                                
            k_r = k_r0 + (1 - k_r0) * pow((1 - cos(phi)) , 5); 
            k_t = 1 - k_r;
        }

        // GIVE COLOR slide 75
        depth--;            
        color = color + k_r * trace(reflectRay, depth); // I = kr * I(P,R)
        color = color + k_t * trace(refractRay, depth);

    }
    else if (depth > 0 and material.ks > 0.0)
    {
        // The object is not transparent, but opaque.
        Vector reflectDirection = reflect(ray.D, shadingN);

        Point hoveringHit = hit + 0.001 * shadingN;

        Ray reflectRay { hoveringHit, reflectDirection };

        // 2.2.4 don't forget to reduce depth
        color = color + obj->material.ks *  trace(reflectRay, depth--);

        // OUR CODE END
    }

    return color;
}

void Scene::render(Image &img)
{
    unsigned w = img.width();
    unsigned h = img.height();

    for (unsigned y = 0; y < h; ++y)
        for (unsigned x = 0; x < w; ++x)
        {
            Point pixel(x + 0.5, h - 1 - y + 0.5, 0);
            Ray ray(eye, (pixel - eye).normalized());
            Color col = trace(ray, recursionDepth);
            col.clamp();
            img(x, y) = col;
        }
}
// old render function used in CG course


void Scene::checkCorrectEye()
{
    for (auto obj : objects)
        obj->checkCorrectEye(eye);      // implement this for all objects!
}
// checks whether the eye is in a bad spot with respect to the object,
// changes that if necessary (e.g. move outside a sphere)

void Scene::SolarSystemSimStep()
{
    double frameVel = 0.01;             // fraction of how many frames it takes
                                        // to let 1 year on earth pass 
                                        // 0.01 -> 100 frames == 1 full orbit of earth

    // Sun, Mercury, Venus, Earth, Moon (Earth), Mars, Jupiter, Saturn, Uranus, Neptune, Pluto
    // 24 -> 2.400 km
    vector<size_t> planetRadii{ 700, 24, 60, 64, 17, 34, 669, 582, 253, 246, 12 };

    // 58 -> 58 million km
    vector<size_t> planetDistances{ 0, 58, 108, 150, 150, 228, 778, 1434, 2871, 4495, 5906 };
    
    // from https://www.sjsu.edu/faculty/watkins/orbital.htm
    vector<double> planetYearLengths{ 0, 0.24, 0.616, 1.0, 1.0, 1.9, 12.0, 29.5, 84, 165, 248 };
   
    vector<ObjectPtr> planets;

    // get all spheres that have a texture -> planet
    for (ObjectPtr &planet : getObjects())
    {
        if (!planet->isSkybox && planet->material.hasTexture)
            planets.push_back(planet);
    }

    double velocityMultiplier = 0;      // movement around sun according to 
                                        // distance -> realistic
    Vector fromSun;                     // to be rotated  

    for (size_t idx = 0; idx < planets.size(); ++idx)
    {
        if (planets[idx]->position.length() == 0)
            continue;                   // ignore the sun itself

        if (idx == 4)                   // moon around the earth as well!
        {
            // get copy of earth
            Vector earth = planets[3]->position;

            Vector earthToMoon = planets[4]->position - earth;

            // pre-rotate earth copy
            velocityMultiplier = 1 / planetYearLengths[3];
            rotateVector(earth, 0, frameVel * velocityMultiplier, 0);

            velocityMultiplier = 1 / (27.322 / 365.25);  // speed of moon around earth
            rotateVector(earthToMoon, 0, frameVel * velocityMultiplier, 0);

            planets[4]->position = earth + earthToMoon;
            continue;
        }
        velocityMultiplier = 1 / planetYearLengths[idx];
                                        // rotate position around Y axis
        rotateVector(planets[idx]->position, 0, frameVel * velocityMultiplier, 0);
    }
}
// MB Rotate the planets around the sun (and the moon around the earth) according
// to their real-world year durations. Adjust 'frameVel' for different speeds.


void Scene::renderToSFImage(sf::Image &img)
{
    checkCorrectEye();                  // corrects eye position if in
                                        // segfault-invoking position

    sf::Vector2u size = img.getSize();
    int w = size.x;
    int h = size.y;                     // could be replaced by SIZE


    Vector down{ 0, -1, 0 };            // vector down from centre of screen
    Vector right{ 1, 0, 0 };            // vector right from centre
    
                                        // no Z-rotation yet
    rotateVector(down, eyeRotation.x, eyeRotation.y, 0);
    rotateVector(right, eyeRotation.x, eyeRotation.y, 0);

                                        // camera perpendicular to screen formed
    Vector d_camera = right.cross(down);// by right+down

    // rotate around the camera for Z-rotation (unfinished)
    // rotateVectorAroundVector(down, d_camera, eyeRotation.z);
    // rotateVectorAroundVector(right, d_camera, eyeRotation.z);
    
    Point screenCentre = eye + d_camera * SIZE * d_zoom;

    // EXPLANATION PERSPECTIVE
    // Imagine the data member 'eye' being the tip of a pyramid that lays on the
    // side (initially without rotation). 'd_camera' points from the tip of the
    // pyramid to the centre of its base, the 'screenCentre'. Since the size of
    // the screen is dependent on 'SIZE', the camera vector is simply multiplied
    // by it, giving a 52° field of view if my calculations are correct.
    // Finally, greater zoom means that the imaginary screen is further away,
    // resulting in the 'screenCentre'. From there, we can use the rotated 'right'
    // and 'down' vectors to get to each individual pixel. We do not have to worry
    // about the screen being inside an object, since it simply provides the 
    // direction of the 'ray'.

    //#pragma acc kernels loop          // experiment with OpenACC
    # pragma omp parallel for
    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            // go from top left to bottom right, using the 3 rotated vectors
            Point pixel = screenCentre + (x - SIZE/2) * right + (y - SIZE/2) * down;

            Ray ray(eye, (pixel - eye).normalized());   // shoot ray through pixel
            Color col = trace(ray, recursionDepth);     
            col.clamp();                                // some spots might be too bright

                                                        // SFML wants 0-255 ints
            img.setPixel(x, y, sf::Color{ static_cast<sf::Uint8>(col.r * 255),  
                                          static_cast<sf::Uint8>(col.g * 255), 
                                          static_cast<sf::Uint8>(col.b * 255) 
                                        }
            );
        }        
    }
}
// MB rewritten render function


// --- Misc functions ----------------------------------------------------------

// Defaults
Scene::Scene()
:
    objects(),
    lights(),
    eye(),
    renderShadows(false),
    recursionDepth(0),
    supersamplingFactor(1)
{}

void Scene::addObject(ObjectPtr obj)
{
    objects.push_back(obj);
}

void Scene::addLight(Light const &light)
{
    lights.push_back(LightPtr(new Light(light)));
}

void Scene::setEye(Triple const &position)
{
    eye = position;
}
// MB

void Scene::setEyeRotation(Triple const &rotation)
{
    eyeRotation = rotation;
}
// MB

void Scene::translateEye(double right, double up, double forward)
{
    Vector direction{ right, up, forward };
    rotateVector(direction, eyeRotation.x, eyeRotation.y, eyeRotation.z);

    eye += direction;
}
// MB receives the amount of translation in each direction, due to the eye's 
// rotation, this has to be converted into the actual x,y,z translation.

unsigned Scene::getNumObject()
{
    return objects.size();
}

unsigned Scene::getNumLights()
{
    return lights.size();
}

void Scene::setRenderShadows(bool shadows)
{
    renderShadows = shadows;
}

void Scene::setRecursionDepth(unsigned depth)
{
    recursionDepth = depth;
}

void Scene::setSuperSample(unsigned factor)
{
    supersamplingFactor = factor;
}

