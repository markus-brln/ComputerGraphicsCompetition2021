#ifndef UTILS_H
#define UTILS_H

#include "../raytracerandfriends/triple.h"
#include <cmath>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

// GLOBALS
extern int SIZE;
//extern int UPSCALED;
extern string SCENE;
extern bool SolarSystemSimOn;
extern double MOVEMENT_MUL;
extern double MOVEMENT_BASE;



// USEFUL FUNCTIONS

double distance2D(double x1, double y1, double x2, double y2);
double distance3D(Triple t1, Triple t2);
double angle(Triple a, Triple b);
void rotateVector(Vector &vec, double x_rot, double y_rot, double z_rot);
void rotateVectorAroundVector(Vector &vec, Vector const &axis, double angle);
void chooseScene();
void modifyMovementSpeed(double factor);
void upscaleSFImage(sf::Image &image);      // failed attempt

#endif

