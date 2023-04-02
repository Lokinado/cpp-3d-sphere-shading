#include <iostream>
#include "vec.h"
using namespace std;

#ifndef ENT_H
#define ENT_H

class entity{
public:
    string Name;
    vec Position;
    vec Direction;
    bool (*IsInEntity)(double, double, double);
    entity(string n, vec pos, vec dir, bool (*func)(double, double, double)){
        this->Position = pos;
        dir.normalize();
        this->Direction = dir;
        this->Name = n;
        this->IsInEntity = func;
    }
    entity(){
        this->Position = vec();
        this->Direction = vec();
        this->Name = "";
        this->IsInEntity = nullptr;
    }
    bool IsPointInside(vec point){
        point = point - this->Position;
        return this->IsInEntity(point.x,point.y,point.z);
    }
    vec GetNormalVector(vec point){
        vec ret(this->Position, point);
        ret.normalize();
        return ret;
    }
};

#endif
