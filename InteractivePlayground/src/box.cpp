//
//  box.cpp
//  InteractivePlayground
//
//  Created by Reuben on 28/07/15.
//
//

#include "box.h"

box::box(){
    
}
//----------------------------------------------
void box::setup(){
    
}
//----------------------------------------------
void box::update(){
    
}
//----------------------------------------------
void box::draw(){
    ofPushMatrix();
    
    ofTranslate(pos);
    ofRotateZ(rot);
    
    ofSetColor(col);
    ofRect(0, 0, 50, 50);
    
    ofPopMatrix();
    
}