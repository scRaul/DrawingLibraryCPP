/*
 PPM class writes ppm3 files. Each pixel
 is colored in using rgb.
 
 covertImage function calls convert.sh
 to converts the ppm files into png
 using pnmtopng.exe
 */

#ifndef PPM__HPP
#define PPM__HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <sys/wait.h>
#include <unistd.h>
#include <thread>

using namespace std; 

struct Color{
    int r;
    int g;
    int b;
    Color(int r,int g, int b):r(r),g(g),b(b){}
};
Color getRandomColor();
class PPM{
    
public:
    PPM(int width, int height,string folderPath);
    void setPixelColor(int x, int y, Color color);
    void createImage(int frame=-1);
    int  getPixelsAcross(){return pixelsAcross;}
    int  getPixelsDown(){return pixelsDown;}
private:
    vector<int> imageData;
    vector<int> blankData;
    int pixelsAcross;
    int pixelsDown;
    int imageCount;
    string folderPath;
    static void convertImage(int frame,string folder);
};



#endif
