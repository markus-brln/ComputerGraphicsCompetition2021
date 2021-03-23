#ifndef UTILS_H
#define UTILS_H

#include "../raytracerandfriends/triple.h"
#include <cmath>
#include <string>

using namespace std;

// GLOBALS
extern int SIZE;
extern string SCENE;


// USEFUL FUNCTIONS

double distance3D(Triple t1, Triple t2);
double angle(Triple a, Triple b);
void rotateVector(Vector &vec, double x_rot, double y_rot, double z_rot);

#endif