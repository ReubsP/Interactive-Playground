//
//  box.h
//  InteractivePlayground
//
//  Created by Reuben on 28/07/15.
//
//

#pragma once
#include "ofMain.h"
#define scaleSize 0.15


class box{
    
public:
    box();
    void setup();
    void update();
    void draw();
    bool mouseIn(int x, int y);
    bool mouseInCentre(int x, int y);
    bool canMoveY(int posx);
    bool canMoveX(int posy);
    int lockToCol(int posx);
    int lockToRow(int posy);
    
    
    
    ofVec2f pos, aim;
    ofPoint posToMouse, mouse;
    float rot, prevRot, newRot, initMouseAngle;
    bool initRotating;
    ofColor col;
    int alpha;
    int size;
    float radius;
    int beams;
    
    bool moving;
    bool selected;
    bool rotating;
    
    
    vector<ofVec2f> lightBeams;
    //int boxHitNum;
    //bool hit;
    
    vector<int> gridX;
    vector<int> gridY;
    
    //positions of all boxes
    vector<ofVec2f> allPos;
    
    
    
    };