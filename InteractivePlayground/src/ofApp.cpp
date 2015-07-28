#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    makeGrid(ofGetWidth(), ofGetHeight(), 5, 5);
    
    b.assign(NumBoxes, box());
    resetBoxes();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::makeGrid(int w, int h, int x, int y){
    gridX.clear();
    gridY.clear();
    
    float xSpace = w/x;
    float ySpace = h/y;
    
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
        b[i].pos.x = gridX[ofRandom(gridX.size())];
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
