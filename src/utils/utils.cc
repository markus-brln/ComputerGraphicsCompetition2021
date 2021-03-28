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
    // ASCII way of writing the matrices & vectors down taken from:
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


void chooseScene()
{
    vector<string> myScenes { "1basic", "2earth", "3mixed", "4sun",
                              "5earthAloneRotation", "6skyboxOnly", "7solSysRealDistProportions",
                              "8fancy", "9solarSystem" };
        cout << "Scenes constructed by me:\n";

    for (auto scene : myScenes)
        cout << "\"../Scenes/myScenes/" + scene + ".json\"\n";
    
    cout << "Enter the number of these scenes or write the relative path of your own.\n\n";

    string userInput;
    getline(cin, userInput);

    size_t szeneNum = 9;
    try 
    {
        szeneNum = stoi(userInput);
        
        SCENE = "../Scenes/myScenes/" + myScenes[szeneNum - 1] + ".json";
    }
    catch (...)
    {
        SCENE = userInput;
    }
}
// ask user for scene, pick from standard or input own relative path


void upscaleSFImage(sf::Image &image)
{
    /*int scalingFactor = UPSCALED / SIZE;
    sf::Image upscale;
    upscale.create(UPSCALED, UPSCALED);

    sf::Color currentColor;

    upscale.setPixel(0, 1, sf::Color{1,1,1});
    
    #pragma omp parallel for
    for (int y = 0; y < SIZE; ++y)
    {
        for (int x = 0; x < SIZE; ++x)
        {
            currentColor = image.getPixel(x, y);
            upscale.setPixel(scalingFactor * x, scalingFactor * y, currentColor);
            upscale.setPixel(scalingFactor * x + 1, scalingFactor * y, currentColor);
            upscale.setPixel(scalingFactor * x, scalingFactor * y + 1, currentColor);
            upscale.setPixel(scalingFactor * x + 1, scalingFactor * y + 1, currentColor);
        }
    }
    sf::Image smoothed;
    smoothed.create(UPSCALED, UPSCALED);
    int r, g, b;

    // smooth all but the edges
    #pragma omp parallel for
    for (int y = 1; y < UPSCALED - 1; ++y)
    {
        for (int x = 1; x < UPSCALED - 1; ++x)
        {
            Color col;
            currentColor = upscale.getPixel(x - 1, y);
            col.r += currentColor.r;
            col.g += currentColor.g;
            col.b += currentColor.b;
            currentColor = upscale.getPixel(x + 1, y);
            col.r += currentColor.r;
            col.g += currentColor.g;
            col.b += currentColor.b;
            currentColor = upscale.getPixel(x, y - 1);
            col.r += currentColor.r;
            col.g += currentColor.g;
            col.b += currentColor.b;
            currentColor = upscale.getPixel(x, y + 1);
            col.r += currentColor.r;
            col.g += currentColor.g;
            col.b += currentColor.b;

            smoothed.setPixel(x, y, sf::Color{ col.r / 4, col.g / 4, col.b / 4 });
        }
    }
    image = smoothed;
    */
}
// failed attempt to upscale+smooth the picture to reduce
// computations

