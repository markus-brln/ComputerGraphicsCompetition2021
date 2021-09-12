/*
Hit SomeShape::intersect(Ray const &ray)
{
    // SomeShape formula: ||x - position||^2 = r^2
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

    if (distance3D(hit, position) < r * 2)
        return Hit(t, N);

    return Hit::NO_HIT();
}
*/