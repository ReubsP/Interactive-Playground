//
//  box.cpp
//  InteractivePlayground
//
//  Created by Reuben on 28/07/15.
//
//

#include "box.h"

box::box(){
    rot = 0;
    prevRot = rot;
    alpha = 255;
    moving = false;
    selected = false;
    rotating = false;
    size = 640*scaleSize;
    radius = ofDist(0,0,size,size)*0.5;
    beams = 5;
}


//----------------------------------------------
void box::setup(){
    col = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
    for (int i=0; i<beams; i++){
        lightBeams.push_back(pos);
    }
}
//----------------------------------------------
void box::update(){
    if(moving){
        
        aim.set(ofGetAppPtr()->mouseX, ofGetAppPtr()->mouseY);
        
        
        if(canMoveY(pos.x)) pos.y = aim.y;
        if(canMoveX(pos.y)) pos.x = aim.x;
        
        //keep on grid
        if (pos.x < gridX[0]) {
            pos.x = gridX[0];
        }
        if (pos.x > gridX[gridX.size()-1]) {
            pos.x = gridX[gridX.size()-1];
        }
        if (pos.y < gridY[0]) {
            pos.y = gridY[0];
        }
        if (pos.y > gridY[gridY.size()-1]) {
            pos.y = gridY[gridY.size()-1];
        }
        
        alpha = 200;
    }
    else{
        alpha = 255;
    }
    
    //rotate
    if (rotating){
        //set mouse position
        mouse.set(ofGetAppPtr()->mouseX, ofGetAppPtr()->mouseY);
        //vector from box position to mouse position
        posToMouse = pos-mouse;
        
        //save the angle between the box and mouse when first selected
        if(initRotating) initMouseAngle = pos.angle(posToMouse);
        
        //rotate by the difference between the initial angle and current angle
        newRot = pos.angle(posToMouse) - initMouseAngle;
        //add the rotation to what it was before
        rot = prevRot + newRot;
        
        initRotating = false;
    }
    else{
        prevRot = rot;
        initRotating = true;
    }
    
    
    
    
    
    //light
    for (int i=0; i<lightBeams.size(); i++) {
        lightBeams[i] = pos;
        bool hitBox = false;
        
        //make "up" direction for rotation reference
        ofVec2f up = ofVec2f(0, -1);
        //find direction of light beam
        ofVec2f lightRot = up.getRotated(rot+i*3-(lightBeams.size()*1.5));
        
        //while the light is less than 500 away and it hasn't hit a box...
        while (lightBeams[i].distance(pos)<1000*scaleSize && !hitBox) {
            //light travels in the direction set by the box's rotation
            lightBeams[i] += lightRot;
            
            //check the positions of all the boxes
            for (int i = 0; i<allPos.size(); i++){
                //if the light is close to a box that isn't it's source
                if(allPos[i].distance(lightBeams[i])<size/2 && allPos[i].distance(pos)>radius){
                    hitBox = true;    //it has hit a box (stop the light going further)
                    //boxHitNum = i;    //ofApp uses this to tell a box that it has been hit
                }
            }
        }
    }
//    lightPos = pos;        //starts at box position
//    bool hitBox = false;   //hasn't hit a box
//    //boxHitNum = -1;        //-1 references no boxes to be rendered as hit
//    
//    //make "up" direction for rotation reference
//    ofVec2f up = ofVec2f(0, -1);
//    
//    //while the light is less than 500 away and it hasn't hit a box...
//    while (lightPos.distance(pos)<1000*scaleSize && !hitBox) {
//        //light travels in the direction set by the box's rotation
//        lightPos += up.getRotated(rot);
//        
//        //check the positions of all the boxes
//        for (int i = 0; i<allPos.size(); i++){
//            //if the light is close to a box that isn't it's source
//            if(allPos[i].distance(lightPos)<size/2 && allPos[i].distance(pos)>radius){
//                hitBox = true;    //it has hit a box (stop the light going further)
//                //boxHitNum = i;    //ofApp uses this to tell a box that it has been hit
//            }
//        }
//    }

}
//----------------------------------------------
void box::draw(){
    ofPushMatrix();
    
    ofTranslate(pos);
    ofRotateZ(rot);
    
    ofSetColor(col, alpha);
    ofRect(0, 0, size, size);
    if(selected){
        ofNoFill();
        ofSetColor(0);
        ofRect(0, 0, size, size);
        ofEllipse(0, 0, radius*2, radius*2);
        ofFill();
    }
    ofPopMatrix();
    
    ofSetColor(255);
    ofSetLineWidth(5);
    for (int i=0; i<lightBeams.size(); i++){
        ofLine(pos, lightBeams[i]);
    }

    ofSetLineWidth(1);
}

//----------------------------------------------
bool box::mouseIn(int x, int y){
    if(pos.distance(ofVec2f(x, y))<radius) return true;
    else return false;
}
//----------------------------------------------
bool box::mouseInCentre(int x, int y){
    if(pos.distance(ofVec2f(x, y))<radius*0.6) return true;
    else return false;
}

//----------------------------------------------
bool box::canMoveY(int posx){
    bool canMove = false;
    for(int i=0; i<gridX.size(); i++){
        //if distance between box pos and grid pos is small
        //and it's not at the top or bottom
        if (ABS(posx-gridX[i]) < 3) {
            pos.x = gridX[i];
            canMove = true;
        }
    }
    return canMove;
}

//----------------------------------------------
bool box::canMoveX(int posy){
    bool canMove = false;
    for(int i=0; i<gridY.size(); i++){
        if (ABS(posy-gridY[i]) < 3) {
            pos.y = gridY[i];
            canMove = true;
        }
    }
    return canMove;
}

