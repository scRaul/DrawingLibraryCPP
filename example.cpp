#include <Canvas.hpp>

//get a copy of points translated x units
vector<vec4> getTransCopy(float x, vector<vec4> points){
    for(int i = 0; i < points.size();i++){
        points[i].x += x;
    }
    return points;
}

int main(){
    
    int width = 500;
    int height = 500;
    //set up ppm file, and path to place images 
    PPM ppm(width,height,"img/");
    //use canvas to draw onto file 
    Canvas canvas(&ppm);
    
    Color c(255,0,0);
    vec4 p(0,0,0,1);
    
    canvas.point(p,c);
    float x, y;
    vector<vec4> points;
    while( cin >> x >> y){
        vec4 p(x*2,y*2,1,1);
        points.push_back(p);
    }
    int spacing = width / 4;
    canvas.draw(DRAW_TYPE::POINT,getTransCopy(-1.25*spacing,points),c);
    canvas.draw(DRAW_TYPE::LINE,getTransCopy(-spacing/2.5,points),c);
    canvas.draw(DRAW_TYPE::BEZIER,getTransCopy(spacing/2.5,points),c);
    canvas.draw(DRAW_TYPE::BSPLINE,getTransCopy(1.25*spacing,points),c);
    c.b = 255;

    //index for the png, file will be saved as index.png
    ppm.createImage(3);
    return 0;
}
