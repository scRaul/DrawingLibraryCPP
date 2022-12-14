#include <PPM.hpp>

Color getRandomColor(){
    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;
    return Color(r,g,b);
}


PPM::PPM(int width,int height,string folderPath){
    pixelsAcross = width;
    pixelsDown = height;
    this->folderPath = folderPath;
    
    int size = pixelsDown * pixelsAcross * 3;
    
    for(int i = 0; i < size; i++){
        imageData.push_back(0);
    }
    blankData = imageData;
    imageCount = 0;
}


void PPM::setPixelColor(int x, int y, Color color){
    int index =  ( pixelsAcross * y + x ) * 3;
    if ( index > imageData.size() || index < 0 ) return;
    imageData[index] = color.r;
    imageData[index+1] = color.g;
    imageData[index+2] = color.b;
}

void PPM::createImage(int frame){
    int f;
    if(frame == -1)
        f = imageCount;
    else
        f = frame;
    string file = folderPath + to_string(f) + ".ppm";
    ofstream image(file.c_str());
    if(image.fail()){
        cerr<<"Failed to write image  " << file << endl;
        cerr<<"Make sure folder path exists: "<< folderPath << endl;
        exit(1);
    }
    cout<<"drawing image #" << f <<endl;
    image << "P3" << endl;
    image << pixelsAcross <<" "<< pixelsDown << endl;
    image << "255" << endl;
    for(int i = 0; i < imageData.size() ; i++){
        image << imageData[i] << " ";
        if(i % pixelsAcross == 0)
            image << endl;
    }
    imageCount++;
    thread _th(convertImage,f,folderPath);
    _th.detach();
    image.close();
    imageData = blankData;
}

void PPM::convertImage(int frame,string folder){
    char *arg[4];
    arg[0] = (char*)"./include/convert.sh";
    arg[1] = (char*) folder.c_str();
    arg[2] = (char*)to_string(frame).c_str();
    arg[3] = NULL;
    pid_t c_pid = fork();
    if(c_pid == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }else if(c_pid > 0){
        wait(0);
        return;
    }else{
        if(execvp(arg[0],arg) == -1)
            perror("execvp");
        exit(EXIT_SUCCESS);
    }
}
