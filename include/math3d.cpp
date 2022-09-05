#include <Math3d.hpp>


vec4::vec4(float x,float y, float z,float w):x(x),y(y),z(z),w(w){}

mat4::mat4(vec4 col1,vec4 col2,vec4 col3,vec4 col4){
    row[0] = vec4(col1.x,col2.x,col3.x,col4.x);
    row[1] = vec4(col1.y,col2.y,col3.y,col4.y);
    row[2] = vec4(col1.z,col2.z,col3.z,col4.z);
    row[3] = vec4(col1.w,col2.w,col3.w,col4.w);
}
mat4::mat4(float f){
    row[0] = vec4(f,0,0,0);
    row[1] = vec4(0,f,0,0);
    row[2] = vec4(0,0,f,0);
    row[3] = vec4(0,0,0,f);
}
mat4::mat4(float a,float b,float c,float d,
           float e,float f,float g,float h,
           float i,float j,float k,float l,
           float m,float n,float o,float p ){
    row[0].x = a; row[0].y = b; row[0].z = c, row[0].w = d;
    row[1].x = e; row[1].y = f; row[1].z = g; row[1].w = h;
    row[2].x = i; row[2].y = j; row[2].z = k; row[2].w = l;
    row[3].x = m; row[3].y = n; row[3].z = o; row[3].w = p;
}


string to_string(const vec4& v){
    return "[" + std::to_string(v.x) +", "+std::to_string(v.y)+", "+std::to_string(v.z)+", "+std::to_string(v.w) +"]";
}
string to_string(const mat4& m){
    string build = to_string( m.row[0] ) + "\n" + to_string( m.row[1] )+"\n"+ to_string( m.row[2] ) + "\n" + to_string(m.row[3]) ;
    return build;
}
std::ostream& operator<<(std::ostream& out, const vec4& v){
    cout <<  to_string(v);
    return out;
}
std::ostream& operator<<(std::ostream& out, const mat4& m){
    cout <<  to_string(m);
    return out;
}
const vec4 operator *(const float s,const vec4& v){
    return vec4(v.x*s,v.y*s,v.z*s,v.w*s);
}
const vec4 operator *(const vec4& v,const float s){
    return vec4(v.x*s,v.y*s,v.z*s,v.w*s);
}
const vec4 operator -(const vec4& v){
    return vec4(v.x*-1,v.y*-1,v.z*-1,v.w*-1);
}
const vec4 operator +(const vec4& v1,const vec4& v2){
    return vec4(v1.x + v2.x,v1.y + v2.y,v1.z + v2.z,v1.w + v2.w);
}



const vec4 operator *(const mat4& m,const vec4& v){
    float x = (m.row[0].x * v.x) + (m.row[0].y * v.y)  + (m.row[0].z * v.z) + (m.row[0].w * v.w) ;
    float y = (m.row[1].x * v.x) + (m.row[1].y * v.y)  + (m.row[1].z * v.z) + (m.row[1].w * v.w) ;
    float z = (m.row[2].x * v.x) + (m.row[2].y * v.y)  + (m.row[2].z * v.z) + (m.row[2].w * v.w) ;
    float w = (m.row[3].x * v.x) + (m.row[3].y * v.y)  + (m.row[3].z * v.z) + (m.row[3].w * v.w) ;
    return vec4(x,y,z,w);
}

const mat4 operator +(const mat4& m1,const mat4& m2){
    mat4 temp(m1.row[0] + m2.row[0],
              m1.row[1] + m2.row[1],
              m1.row[2] + m2.row[2],
              m1.row[3] + m2.row[3]);
    return transpose(temp);
}
const mat4 operator -(const mat4& m){
    mat4 temp( -1*m.row[0],-1*m.row[1],-1*m.row[2], -1*m.row[3]);
    return transpose(temp);
}
const mat4 operator -(const mat4& m1,const mat4& m2){
    mat4 temp( m1.row[0] + -m2.row[0],
               m1.row[1] + -m2.row[1],
               m1.row[2] + -m2.row[2],
               m1.row[3] + -m2.row[3]);
    return transpose(temp);
}
const mat4 operator *(const float s,const mat4& m){
    vec4 col1 = s*m.row[0];
    vec4 col2 = s*m.row[1];
    vec4 col3 = s*m.row[2];
    vec4 col4 = s*m.row[3];
    return mat4(col1.x,col1.y,col1.z,col1.w,
                col2.x,col2.y,col2.z,col2.w,
                col3.x,col3.y,col3.z,col3.w,
                col4.x,col4.y,col4.z,col4.w);
}
const mat4 operator *(const mat4& m,const float s){
    return s * m;
}
const mat4 operator *(const mat4& m1,const mat4 &m2){
    vec4 c1 = m1 * m2.row[0];
    vec4 c2 = m1 * m2.row[1];
    vec4 c3 = m1 * m2.row[2];
    vec4 c4 = m1 * m2.row[4];
    return mat4(c1.x,c2.x,c3.x,c4.x,
                c1.y,c2.y,c3.y,c4.y,
                c1.z,c2.z,c3.z,c4.z,
                c1.w,c2.w,c3.w,c4.w);
}
const mat4 transpose(const mat4& m){
    vec4 c1 = m.row[0];
    vec4 c2 = m.row[1];
    vec4 c3 = m.row[2];
    vec4 c4 = m.row[4];
    return mat4(c1.x,c2.x,c3.x,c4.x,
                c1.y,c2.y,c3.y,c4.y,
                c1.z,c2.z,c3.z,c4.z,
                c1.w,c2.w,c3.w,c4.w);
}
