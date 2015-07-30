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
    
    ofVec2f pos;
    float rot;
    ofColor col;
};