#pragma once

#include "ofMain.h"
#include "box.h"
#define numBoxes 7
#define scaleSize 0.15

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    
    void makeGrid(int w, int h, int x, int y);
    void resetBoxes();
    
    
    vector<box> b;
    
    vector<int> gridX;
    vector<int> gridY;
    

};
