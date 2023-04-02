#include <iostream>
#include <vector>
#include <cstdio>
#include "vec.h"
#include "camera.h"
#include "entity.h"
using namespace std;


vector<entity> scene;
static bool sph(double x, double y, double z){
    double dist = x*x + y*y + z*z;
    if(dist <= 49.0) return true;
    else return false;
}

int main()
{
    freopen("output.txt","w",stdout);
    entity sphere("sphere", vec(30,0,0), vec(1,0,0), sph);
    scene.push_back(sphere);

    camera cam(vec(0,0,0), vec(1,0,0),160,80,1);
    cam.update(scene);

    return 0;
}
