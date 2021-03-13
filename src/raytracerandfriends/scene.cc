#include "scene.h"

#include "hit.h"
#include "image.h"
#include "material.h"
#include "ray.h"

#include <algorithm>
#include <cmath>
#include <limits>

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

double distance3D(Triple t1, Triple t2)
{
    return sqrt(pow(t1.x - t2.x, 2) + pow(t1.y - t2.y, 2) + pow(t1.z - t2.z, 2));
}

bool Scene::lightObstructed(LightPtr const &light, Point const &hit, Vector const &normalFromObj)
{
                                        // from the hitpoint + some N dir to view
    Point hoveringHit = hit + epsilon * normalFromObj;


    Ray shadowRay = Ray{ hoveringHit, light->position - hoveringHit};

    pair<ObjectPtr, Hit> mainhit = castRay(shadowRay);
    
    
    if (!mainhit.first)      // first == object pointer, nullptr if no hit
        return false;                   // No hit? No obstruction.


    Point objHitPoint = shadowRay.O + mainhit.second.t * shadowRay.D;
    if (distance3D(light->position, hoveringHit) < distance3D(objHitPoint, hoveringHit))
        return false;
    
    return true;
}
// look whether the light source is obstructed from its origin to the point
// where it would hit the object

double angle(Triple a, Triple b)
{
    return std::acos(a.dot(b)/(a.length()*b.length()));
}
// angle between 2 3D vectors

Color Scene::trace(Ray const &ray, unsigned depth)
{
    pair<ObjectPtr, Hit> mainhit = castRay(ray);
    ObjectPtr obj = mainhit.first;
    Hit min_hit = mainhit.second;

    // No hit? Return background color.
    if (!obj)
        return Color(0.0, 0.0, 0.0);

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

    Color matColor = material.color;

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

#include <omp.h>
void Scene::renderToSFImage(sf::Image &img)
{
    sf::Vector2u size = img.getSize();
    unsigned w = size.x;
    unsigned h = size.y;
    //unsigned w = img.width();
    //unsigned h = img.height();
        
    # pragma omp parallel for
    for (unsigned y = 0; y < h; ++y)
        for (unsigned x = 0; x < w; ++x)
        {
            Point pixel(x + 0.5, h - 1 - y + 0.5, 0);
            Ray ray(eye, (pixel - eye).normalized());
            Color col = trace(ray, recursionDepth);
            col.clamp();
            
            img.setPixel(x, y, sf::Color{ int{255 * col.r}, int{255 * col.g}, int{255 * col.b} } );
            //img(x, y) = col;
        }
}
// MB 
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
