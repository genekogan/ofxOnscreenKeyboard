#include "ofxOnscreenKeyboard.h"


//--------------------------------------------------------------
ofxOnscreenKeyboard::ofxOnscreenKeyboard() {
    
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::setup() {

    font.load("Helvetica.ttf", 28);
    
    ofAddListener(ofEvents().mouseMoved, this, &ofxOnscreenKeyboard::mouseMoved);
    ofAddListener(ofEvents().mousePressed, this, &ofxOnscreenKeyboard::mousePressed);
    ofAddListener(ofEvents().mouseDragged, this, &ofxOnscreenKeyboard::mouseDragged);
    ofAddListener(ofEvents().mouseReleased, this, &ofxOnscreenKeyboard::mouseReleased);

    
    int kX = 20;
    int kY = 10;
    
    int keyW = 80;
    int keyH = 70;
    int margin = 10;
    
    string keyStr[26] = {"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "A", "S", "D", "F", "G", "H", "J", "K", "L", "Z", "X", "C", "V", "B", "N", "M"};
    
    for (int i=0; i<26; i++) {
        int x, y;
        if (i < 10) {
            x = kX + i * (keyW + margin);
            y = kY;
        } else if (i < 19) {
            x = kX + (keyW * 0.333) + (i-10) * (keyW + margin);
            y = kY + 1 * (keyH + margin);
        } else if (i < 26) {
            x = kX + (keyW * 0.666) + (i-19) * (keyW + margin);
            y = kY + 2 * (keyH + margin);
        }
        
        ofxOnscreenKey *key = new ofxOnscreenKey();
        key->setup(keyStr[i], x, y, keyW, keyH);
        key->setKey(keyStr[i]);
        key->setFont(&font);
        key->setBackgroundColor(ofColor::green);
        keys.push_back(key);
        ofAddListener(key->clickEvent, this, &ofxOnscreenKeyboard::keyClicked);
    }
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::draw() {
    for (int i=0; i<keys.size(); i++) {
        keys[i]->draw();
    }
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::mouseMoved(int x, int y) {
    for (int i=0; i<keys.size(); i++) {
        keys[i]->mouseMoved(x, y);
    }
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::mouseDragged(int x, int y) {
    for (int i=0; i<keys.size(); i++) {
        keys[i]->mouseDragged(x, y);
    }

}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::mousePressed(int x, int y) {
    for (int i=0; i<keys.size(); i++) {
        keys[i]->mousePressed(x, y);
    }
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::mouseReleased(int x, int y) {
    for (int i=0; i<keys.size(); i++) {
        keys[i]->mouseReleased(x, y);
    }
}



