//
//  ImageSaver.h
//  ofxTrueTypeFontUCTest
//
//  Created by Shin on 2/22/16.
//
//

#ifndef ofxTrueTypeFontUCTest_ImageSaver_h
#define ofxTrueTypeFontUCTest_ImageSaver_h

class ImageSaver : public ofThread{
public:
    string fileName;
    ofImage image;
    
    void threadedFunction() {
        if(lock()) {
            image.save(fileName);
            unlock();
        } else {
            printf("ofxThreadedImageSaver - cannot save %s cos I'm locked", fileName.c_str());
        }
        stopThread();
    }
    
    void saveThreaded(string fileName) {
        this->fileName = fileName;
        startThread(false, false);   // blocking, verbose
    }
    
    void grabScreen(int x, int y, int w, int h){
        image.grabScreen(0, 0, w, h);
    }
};

#endif
