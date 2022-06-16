#include "mandelbrot.h"
#include "solvers.h"

#include <cmath>
#include <complex>

using namespace std;

size_t mandel_loop(double real, double imag, size_t maxIter)
{
    std::complex<double> c{ real, imag };
    std::complex<double> z{ 0.0, 0.0 };

    
    size_t idx = 0;
    for (; idx < maxIter; ++idx)
    {
        z = z*z + c;
        if (z.real() *z.real() + z.imag() * z.imag() >= 4)
            return idx;
    }
    return maxIter;
}

Hit Mandelbrot::intersect(Ray const &ray)
{
    // Line formula:   x = ray.O + t * ray.D
    Vector N = axis;

    // Catch the case where the ray is parallel to the plane, i.e. no intersection.
    double DdotN = (-ray.D).dot(N);
    if (std::abs(DdotN) < std::numeric_limits<double>::epsilon())
        return Hit::NO_HIT();

    // Find the point of intersection with the plane.
    double t = -N.dot(ray.O - position) / N.dot(ray.D);

    if (t < 0.0)
        return Hit::NO_HIT();

    Point hit = ray.at(t);

    double mandelSize = 200;

    double real = (position.x - hit.x) / mandelSize;
    double imag = (position.z - hit.z) / mandelSize;
    size_t maxIter = 50;

    double mandel = mandel_loop(real, imag, maxIter);
    
    if (mandel == maxIter) {
        return Hit::NO_HIT();
    }
    else {
        Hit new_hit = Hit(t, N);
        new_hit.has_color = true;
        double zn = sqrt(real * real + imag * imag);
        new_hit.col = Color(
            mandel + 50 - 50 * (log(2) / zn ) / log(2),
            1.0 * mandel / 2 + 50 - 50 * (log(2) / (zn * 0.5) ) / log(2),
            mandel + 50 - 50 * (log(2) / zn ) / (0.8 * log(2))
        );
        // new_hit.col = Color(
        //     (1 - sin(0.05 * mandel)) / 2,
        //     (1 - cos(0.3 * mandel)) / 2, 
        //     (1 - cos(0.15 * mandel)) / 2
        // );
        return new_hit;
    }

    /*Vector L = ray.O - position;
    double a = ray.D.dot(ray.D);
    double b = 2.0 * ray.D.dot(L);
    double c = L.dot(L) - r * r;

    double t0;
    double t1;
    if (not Solvers::quadratic(a, b, c, t0, t1))
        return Hit::NO_HIT();

    // t0 is closest hit
    if (t0 < 0.0)  // check if it is not behind the camera
    {
        t0 = t1;    // try t1
        if (t0 < 0.0) // both behind the camera
            return Hit::NO_HIT();
    }

    // calculate normal
    Point hit = ray.at(t0);
    Vector N = (hit - position).normalized();

    // Note that the direction of the normal is not changed here,
    // but in scene.cpp - if necessary.

    return Hit(t0, N);*/
}

#include <iostream>

Vector Mandelbrot::toUV(Point const &hit)
{
    // slide 10-12: map x,y,z coordinates to UV
    double x = hit.x - position.x;
    double y = hit.y - position.y;
    double z = hit.z - position.z;

    // MB xyz were changed to zxy -> poles are now up, "90 degree rotation around x"
    double u = 0.5 + (atan2(x, z) / (2 * PI));
    double v = 1 - (acos(y / r) / PI);

    // Use a Vector to return 2 doubles. The third value is never read.
    return Vector{u, v, 0.0};
}

Mandelbrot::Mandelbrot(Point const &pos, double radius, Vector const& axis, double angle)
:
    // Feel free to modify this constructor.
    //position(pos),
    r(radius),
    axis(axis),
    angle(angle)
{
    this->position = pos;       // MB member moved to base class to change
                                // it in Scene
}

void Mandelbrot::checkCorrectEye(Point &eye)
{
    // Set movement speed based on distance to the plane
    // modifyMovementSpeed(eye.z);

    // if (distance3D(eye, position) < r)
    //     eye += (eye - position).normalized() * 30;
}
// MB push the eye/camera back by the amount it can maximally go -> 30 units