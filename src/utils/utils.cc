#include "utils.h"

double distance3D(Triple t1, Triple t2)
{
    return sqrt(pow(t1.x - t2.x, 2) + pow(t1.y - t2.y, 2) + pow(t1.z - t2.z, 2));
}
// distance between 2 3D points

double angle(Triple a, Triple b)
{
    return std::acos(a.dot(b)/(a.length()*b.length()));
}
// angle between 2 3D vectors


void rotateVector(Vector &vec, double x_rot, double y_rot, double z_rot)
{
    // ACII way of writing the matrices & vectors down taken from:
    // https://stackoverflow.com/questions/14607640/rotating-a-vector-in-3d-space

    // rotation around x
    //|1     0           0| |x|   |        x        |   |x'|
    //|0   cos θ    −sin θ| |y| = |y cos θ − z sin θ| = |y'|
    //|0   sin θ     cos θ| |z|   |y sin θ + z cos θ|   |z'|
    Vector vecCopy{vec};
    // vec.x = same
    vec.y = vecCopy.y * cos(x_rot) - vecCopy.z * sin(x_rot);
    vec.z = vecCopy.y * sin(x_rot) + vecCopy.z * cos(x_rot);

    // roation around y
    //| cos θ    0   sin θ| |x|   | x cos θ + z sin θ|   |x'|
    //|   0      1       0| |y| = |         y        | = |y'|
    //|−sin θ    0   cos θ| |z|   |−x sin θ + z cos θ|   |z'|
    vecCopy = vec;
    vec.x = vecCopy.x * cos(y_rot) + vecCopy.z * sin(y_rot);
    // vec.y = same
    vec.z = -vecCopy.x * sin(y_rot) + vecCopy.z * cos(y_rot);

    // rotation around z
    // |cos θ   −sin θ   0| |x|   |x cos θ − y sin θ|   |x'|
    // |sin θ    cos θ   0| |y| = |x sin θ + y cos θ| = |y'|
    // |  0       0      1| |z|   |        z        |   |z'|
    vecCopy = vec;
    vec.x = vecCopy.x * cos(z_rot) - vecCopy.y * sin(z_rot);
    vec.y = vecCopy.x * sin(z_rot) + vecCopy.y * cos(z_rot);
    // vec.z = same
}
// operates on ref of Vector obj