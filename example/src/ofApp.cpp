#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    keyboard.setup(LAYOUT_GERMAN);
    keyboard.setPosition(50, 200, 80, 70, 30, 10);
    keyboard.setMouseEventsAuto(true);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    keyboard.draw();    
    
    string input = keyboard.getInput();
    ofDrawBitmapString(input, 20, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key==' ') {
        keyboard.toggleVisible();
    }
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
