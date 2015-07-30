//
//  box.h
//  InteractivePlayground
//
//  Created by Reuben on 28/07/15.
//
//

#pragma once
#include <ofMain.h>


class box{
    
public:
    box();
    void setup();
    void update();
    void draw();
    bool mouseIn(int x, int y);
    bool canMoveY(int posx);
    bool canMoveX(int posy);
    
    ofVec2f pos, aim, force, vel;
    float rot;
    ofColor col;
    int alpha;
    int size;
    float radius;
    
    bool moving;
    bool selected;
    
    
    vector<int> gridX;
    vector<int> gridY;
};