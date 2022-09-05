#ifndef Canvas__H
#define Canvas__H

#include <PPM.hpp>
#include <Math3d.hpp>

enum DRAW_TYPE{
    POINT,LINE,BEZIER,BSPLINE
};
//Helper class to draw points, lines and curves, refrences a PPM object
class Canvas{
    
public:
    Canvas(PPM *ppm);
    
    void draw(DRAW_TYPE type,const vector<vec4> points,const Color& color);
    void point(const vec4& point,const Color& color );
    void line(const vec4& from,const vec4& to,const Color& color);
    
private:
    PPM *ppm;
    mat4 screenBasis;

};




#endif
