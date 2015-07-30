#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    makeGrid(ofGetWidth(), ofGetHeight(), 5, 5);
    
    numBoxes = 10;
    b.assign(numBoxes, box());
    resetBoxes();
    
    
    ofSetRectMode(OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0; i<b.size(); i++){
        b[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    //draw grid lines
    ofSetColor(1);
    for (int i = 0; i<gridX.size(); i++){
        ofLine(gridX[i], gridY[0], gridX[i], gridY[gridY.size()-1]);
    }
    for (int i = 0; i<gridY.size(); i++){
        ofLine(gridX[0], gridY[i], gridX[gridX.size()-1], gridY[i]);
    }
    
    //draw grid points
    for (int i = 0; i<gridX.size(); i++){
        for (int j = 0; j<gridY.size(); j++){
            ofSetColor(0);
            ofEllipse(gridX[i], gridY[j], 10, 10);
        }
    }
    
    //draw boxes
    for (int i = 0; i<b.size(); i++) {
        b[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::makeGrid(int w, int h, int x, int y){
    gridX.clear();
    gridY.clear();
    
    float xSpace = w/(x+1);
    float ySpace = h/(y+1);
    
    for(int i=xSpace; i <= w-xSpace; i += xSpace){
        gridX.push_back(i);
    }
    
    for(int i=ySpace; i <= h-ySpace; i += ySpace){
        gridY.push_back(i);
    }
}

//--------------------------------------------------------------
void ofApp::resetBoxes(){
    for(int i = 0; i<b.size(); i++){
        b[i].pos.x = gridX[i/gridX.size()];
        b[i].pos.y = gridY[(i%gridY.size())];
        b[i].setup();
        b[i].gridX = gridX;
        b[i].gridY = gridY;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    for(int i = 0; i<b.size(); i++){
        b[i].selected = false;
        //select the box
        if(b[i].mouseIn(x,y) && !b[i].mouseInCentre(x, y)){
            b[i].selected =true;
        }
        //move the box from the middle
        if(b[i].mouseInCentre(x, y)) b[i].moving = true;
    }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    for(int i = 0; i<b.size(); i++){
        if(b[i].moving){
            b[i].moving = false;
        }
    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
