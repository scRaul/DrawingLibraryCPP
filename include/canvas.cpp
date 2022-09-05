#include <Canvas.hpp>
#include<iostream>

Canvas::Canvas(PPM *ppm):ppm(ppm){
    int width = ppm->getPixelsAcross();
    int height = ppm->getPixelsDown();
    screenBasis = mat4(1,0,0,(width/2.0),
                   0,-1,0,(height/2.0),
                   0,0,1,0,
                   0,0,0,1);
}
void Canvas::draw(DRAW_TYPE type,const vector<vec4> points,const Color& color){
    mat4 basis;
    int step = 1;
    switch(type){
        case DRAW_TYPE::POINT:{
            for(int i = 0; i < points.size();i++)
                Canvas::point(points[i],color);
            return;
        }
        case DRAW_TYPE::LINE:{
            for(int i = 0; i < points.size()-1;i++)
                Canvas::line(points[i],points[i+1],color);
            return;
        }
        case DRAW_TYPE::BEZIER:{
            basis = mat4(1,-3,3,-1,
                    0,3,-6,3,
                    0,0,3,-3,
                    0,0,0,1);
            step = 3;
            break;
        }
        case DRAW_TYPE::BSPLINE:{
            basis = mat4(1,-3,3,-1,
                       4,0,-6,3,
                       1,3,3,-3,
                       0,0,0,1);
            basis = (1/6.0) * basis;
            step = 1;
            break;
        }
    }
    for(int i = 0; i < points.size()-3; i += step){
        mat4 cntrlP(points[i],points[i+1],points[i+2],points[i+3]);
        for(float t = 0.0; t < 1.0; t += .001 ){
            vec4 nomial(1,t,(t*t), (t*t*t) );
            vec4 p = cntrlP*(basis*nomial);
            Canvas::point(p,color);
        }
    }
}
void Canvas::point(const vec4& point,const Color& color ){
    vec4 p = screenBasis * point;
    ppm->setPixelColor(floor(p.x),floor(p.y),color);
}
void Canvas::line(const vec4& from,const vec4& to,const Color& color){
    float x = from.x;
    float y = from.y;
    float dx = to.x - from.x;
    float dy = to.y - from.y;
    int sx = ( dx < 0 ) ? -1 : 1;
    int sy = ( dy < 0 ) ? -1 : 1;
    dx *= sx;
    dy *= sy;
    if( dx >= dy ){
      float X = to.x;
      float p = 2*dy  - dx;
      while( floor(X) != floor(x)   ){
          vec4 tp(x,y,1,1);
          Canvas::point(tp, color);
          x += sx;
          if( p < 0){
              p += 2*dy;
          }else{
              p += 2*dy - 2*dx;
              y +=sy;
          }
      }
    }else{
      float Y = to.y;
      float p = 2*dx  - dy;
      while( floor(Y) != floor(y)  ){
          vec4 tp(x,y,1,1);
          Canvas::point(tp, color);
          y += sy;
          if( p < 0){
            p += 2*dx;
          }else{
            p += 2*dx - 2*dy;
            x += sx;
          }
      }
    }
}

