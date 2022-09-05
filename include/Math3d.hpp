#ifndef MATH3__H
#define MATH3__H
#include <iostream>
#include <cmath>
using std::cout;
using std::string;
struct vec4{
    float x;
    float y;
    float z;
    float w;
    vec4(float x=0.0,float y=0.0, float z=0.0,float w=0.0);
};
struct mat4{
    vec4 row[4];
    void set();
    mat4(vec4 col1,vec4 col2,vec4 col3,vec4 col4);
    mat4(float f);
    mat4(float a=0,float b=0,float c=0,float d=0,
         float e=0,float f=0,float g=0,float h=0,
         float i=0,float j=0,float k=0,float l=0,
         float m=0,float n=0,float o=0,float p=0 );
    
};

string to_string(const vec4& v);
string to_string(const mat4& m);
std::ostream& operator<<(std::ostream& out, const vec4& v);
std::ostream& operator<<(std::ostream& out, const mat4& m);
const vec4 operator *(const float s,const vec4& v);
const vec4 operator *(const vec4& v,const float s);
const vec4 operator -(const vec4& v);
const vec4 operator +(const vec4& v1,const vec4& v2);
const vec4 operator *(const mat4& m,const vec4& v);
const mat4 operator +(const mat4& m1,const mat4& m2);
const mat4 operator -(const mat4& m);
const mat4 operator -(const mat4& m1,const mat4& m2);
const mat4 operator *(const float s,const mat4& m);
const mat4 operator *(const mat4& m,const float s);
const mat4 operator *(const mat4& m1,const mat4 &m2);
const mat4 transpose(const mat4& m);

#endif
