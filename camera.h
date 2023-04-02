#include <iostream>
#include <math.h>
#include <vector>
#include "vec.h"
#include "entity.h"
using namespace std;

#ifndef CAM_H
#define CAM_H

class camera : public entity{
private:
    double degToRad(double angle){
        return angle * (M_PI / 180);
    }
    double radToDeg(double angle){
        return angle * (180 / M_PI);
    }
    double getScreenWidth(){
        double c = this->ScreenDistance / cos( this->degToRad(this->Fov/2.0) );
        double x = c*c - (this->ScreenDistance * this->ScreenDistance);
        return 2*sqrt(x);
    }
    double getCorrectionFactor(double ang){
        return 1.0 / tan(ang);
    }
    static bool AlwaysNotInShape(double x, double y, double z){
        return false;
    }
    char charset[10] = { ' ' , '.' , ':' , '-' , '=' , '+' , '*' , '%' , '#' , '@' };
public:
    //settings
    int Width;
    int Height;
    int BinaryIterations = 20;
    double ScreenDistance;
    double Fov = 30.0;
    double RenderDistance = 90.0;
    double RenderStep = 1.0;
    double ** brightness;

    camera(vec pos, vec dir, int w, int h, double r): entity("CAM", pos, dir, this->AlwaysNotInShape){
        this->Width = w;
        this->Height = h;
        this->ScreenDistance = r;

        brightness = new double*[Height];
        for(int i = 0; i < Height; ++i){
            brightness[i] = new double[Width];
        }
    }
    void update(vector<entity> actors){
        double a = (this->getScreenWidth() / (double)Width);
        double ang = vec(0,0,1).angle(this->Direction);
        vec temp(this->Direction.x,this->Direction.y,0.0);
        temp.normalize();
        vec correctionVector = temp * this->getCorrectionFactor(ang);

        vec upVector = vec(0,0,1) - correctionVector;
        upVector.normalize();

        vec rightVector = this->Direction * upVector;
        rightVector = rightVector * (-1);
        rightVector.normalize();

        upVector = upVector * a * 2;
        rightVector = rightVector * a;

        vec root = this->Direction * this->ScreenDistance;
        vec offset(0.0,0.0,0.0);
        offset = ( upVector * (((double)Height) / 2.0) ) + ( rightVector * (((double)Width) / 2.0) );
        offset = offset * (-1);

        for(int i = 0 ; i < (int)actors.size(); i++){
            for(int h = 0 ; h < Height; h++){
                for(int w = 0 ; w < Width; w++){
                    vec pos(root.x,root.y,root.z);
                    pos = pos + offset + upVector * (double)h + rightVector * (double)w;

                    vec screenMid = pos + upVector * 0.5 + rightVector * 0.5;

                    vec step(this->Position, screenMid);
                    step.normalize();
                    step = step * RenderStep;
                    vec ray = screenMid;
                    bool doesRayIntersect = false;
                    while( vec(this->Position, ray).length() <= RenderDistance){
                        if(actors[i].IsPointInside(ray)){
                            doesRayIntersect = true;
                            break;
                        }
                        ray = ray + step;
                    }
                    if(doesRayIntersect){
                        vec pocz = ray - step;
                        vec kon = ray;
                        vec mid = (pocz + kon) * 0.5;
                        for(int j = 0 ; j < this->BinaryIterations; j++){
                            if( actors[i].IsPointInside(mid) ){
                                kon = vec(mid.x,mid.y,mid.z);
                                mid = (pocz + kon) * 0.5;
                            } else {
                                pocz = vec(mid.x,mid.y,mid.z);
                                mid = (pocz + kon) * 0.5;
                            }
                        }
                        vec normal = actors[i].GetNormalVector(mid);
                        double angle = normal.angle(vec(0,0,-1));
                        double lightlevel = max(1-(angle/(0.5*M_PI)),0.0);
                        cout<<charset[9 - (int)(lightlevel * 10.0)];
                    } else {
                        cout<<"@";
                    }
                }
                cout<<endl;
            }
        }
    }
};

#endif
