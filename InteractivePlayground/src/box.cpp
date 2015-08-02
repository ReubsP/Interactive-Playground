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
    rot = 0;
    prevRot = rot;
    col = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
    alpha = 255;
    moving = false;
    selected = false;
    size = 50;
    radius = ofDist(0,0,size,size)*0.5;
    //boxHitNum = -1;
    //hit = false;
    

}
//----------------------------------------------
void box::update(){
    if(moving){
        
        aim.set(ofGetAppPtr()->mouseX, ofGetAppPtr()->mouseY);
        //ofPoint attractPt(ofGetMouseX(), ofGetMouseY(), 0);
        force = aim-pos; // we get the attraction force/vector by looking at the mouse pos relative to our pos
        
        
        //float dist = force.length();
        
        //force.normalize(); //by normalizing we disregard how close the particle is to the attraction point
        
        
        vel *= 0.6; //apply drag
        vel += force; //apply force
        
        if(canMoveY(pos.x)) pos.y += vel.y;
        if(canMoveX(pos.y)) pos.x += vel.x;
        
        
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
    if (selected){
        //set mouse position
        mouse.set(ofGetAppPtr()->mouseX, ofGetAppPtr()->mouseY);
        //vector from box position to mouse position
        posToMouse = pos-mouse;
        
        //save the angle between the box and mouse when first selected
        if(initSelect) initMouseAngle = pos.angle(posToMouse);
        
        //rotate by the difference between the initial angle and current angle
        newRot = pos.angle(posToMouse) - initMouseAngle;
        //add the rotation to what it was before
        rot = prevRot + newRot;
        
        initSelect = false;
    }
    else{
        prevRot = rot;
        initSelect = true;
    }
    
    
    //light
    lightPos = pos;
    bool hitBox = false;
    //boxHitNum = -1;
    ofVec2f up = ofVec2f(0, -1);
    while (lightPos.distance(pos)<500 && !hitBox) {
        lightPos += up.getRotated(rot);
        for (int i = 0; i<allPos.size(); i++){
            if(allPos[i].distance(lightPos)<size/2 && allPos[i].distance(pos)>radius){
                hitBox = true;
//                boxHitNum = i;
            }
        }
    }

}
//----------------------------------------------
void box::draw(){
    ofPushMatrix();
    
    ofTranslate(pos);
    ofRotateZ(rot);
    
    ofSetColor(col, alpha);
    ofRect(0, 0, size, size);
    if(selected && !moving){
        ofNoFill();
        ofSetColor(0);
        ofRect(0, 0, size, size);
        ofEllipse(0, 0, radius*2, radius*2);
        ofFill();
    }
    ofPopMatrix();
    
    ofLine(pos, lightPos);
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
        if (ABS(posx-gridX[i]) < 2) {
            canMove = true;
        }
    }
    return canMove;
}

//----------------------------------------------
bool box::canMoveX(int posy){
    bool canMove = false;
    for(int i=0; i<gridY.size(); i++){
        if (ABS(posy-gridY[i]) < 2) {
            canMove = true;
        }
    }
    return canMove;
}