#include <iostream>
#include <math.h>
using namespace std;

#ifndef VEC_H
#define VEC_H

class vec{
    public:
        double x;
        double y;
        double z;
        double length(){
            return sqrt( (this->x)*(this->x) + (this->y)*(this->y) + (this->z)*(this->z) );
        }
        void normalize(){
            vec v(this->x,this->y,this->z);
            v = v * (1.0 / v.length());
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
        }
        double dotProd(vec lhs){
            return this->x*lhs.x + this->y*lhs.y + this->z*lhs.z;
        }
        double angle(vec lhs){
            double dotprod = this->dotProd(lhs);
            return acos( dotprod / (lhs.length() * this->length()) );
        }
        vec(double a, double b, double c){
            x = a;
            y = b;
            z = c;
        }
        vec(vec p1, vec p2){
            x = p2.x - p1.x;
            y = p2.y - p1.y;
            z = p2.z - p1.z;
        }
        vec(){
            x = 0;
            y = 0;
            z = 0;
        }
        vec operator+(const vec& lhs){
            return vec(this->x+lhs.x,this->y+lhs.y,this->z+lhs.z);
        }
        vec operator-(const vec& lhs){
            return vec(this->x-lhs.x,this->y-lhs.y,this->z-lhs.z);
        }
        vec operator*(const vec& lhs){
            double s1 = this->y * lhs.z - this->z * lhs.y;
            double s2 = this->z * lhs.x - this->x * lhs.z;
            double s3 = this->x * lhs.y - this->y * lhs.x;
            return vec(s1,s2,s3);
        }
        vec operator+(const double& lhs){
            return vec(this->x+lhs,this->y+lhs,this->z+lhs);
        }
        vec operator-(const double& lhs){
            return vec(this->x-lhs,this->y-lhs,this->z-lhs);
        }
        vec operator*(const double& lhs){
            return vec(this->x*lhs,this->y*lhs,this->z*lhs);
        }
        friend ostream& operator<<(ostream& os, const vec& dt);
};

ostream& operator<<(ostream& os, const vec& dt)
{
    os << '(' << dt.x << ',' << dt.y << ',' << dt.z << ')';
    return os;
}

#endif
