#include "ofxOnscreenKeyboard.h"


// spacebar
// backspace
// preview box
// cosmetics + rounding
// hide or not


//--------------------------------------------------------------
void ofxOnscreenKey::setKey(string key) {
    this->key = key;
    setName(key);
}

//--------------------------------------------------------------
void ofxOnscreenKey::setUpperCase(bool upper) {
    setKey(upper ? ofToUpper(key) : ofToLower(key));
}

//--------------------------------------------------------------
ofxOnscreenKeyboard::ofxOnscreenKeyboard() {
    visible = true;
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::setup() {

    font.load("verdana.ttf", 30);
    
    ofAddListener(ofEvents().mouseMoved, this, &ofxOnscreenKeyboard::mouseMoved);
    ofAddListener(ofEvents().mousePressed, this, &ofxOnscreenKeyboard::mousePressed);
    ofAddListener(ofEvents().mouseDragged, this, &ofxOnscreenKeyboard::mouseDragged);
    ofAddListener(ofEvents().mouseReleased, this, &ofxOnscreenKeyboard::mouseReleased);

    string keyStr[30] = {"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "A", "S", "D", "F", "G", "H", "J", "K", "L", "Z", "X", "C", "V", "B", "N", "M", ".", " ", "^", "<"};
    
    for (int i=0; i<30; i++) {
        ofxOnscreenKey *key = new ofxOnscreenKey();
        key->setup(keyStr[i], 0, 0, 1, 1);
        key->setKey(keyStr[i]);
        key->setFont(&font);
        key->setBackgroundColor(ofColor::lightGray);
        keys.push_back(key);
        ofAddListener(key->clickEvent, this, &ofxOnscreenKeyboard::keyClicked);
    }
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::setVisible(bool visible) {
    this->visible = visible;
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::setPosition(int kX, int kY, int keyW, int keyH) {
    
    
    int margin = 10;
    
    ofVec2f tl(1e8, 1e8);
    ofVec2f br(-1e8, -1e8);
    

    
    for (int i=0; i<30; i++) {
        int x, y;
        if (i < 10) {
            x = kX + i * (keyW + margin);
            y = kY;
        } else if (i < 19) {
            x = kX + (keyW * 0.333) + (i-10) * (keyW + margin);
            y = kY + 1 * (keyH + margin);
        } else if (i < 27) {
            x = kX + (keyW * 0.666) + (i-19) * (keyW + margin);
            y = kY + 2 * (keyH + margin);
        } else if (i < 30) {
            x = kX + (keyW * 0.0) + (i-27) * (keyW + margin);
            y = kY + 3 * (keyH + margin);
        }
        
        tl.x = min(tl.x, (float) x);
        tl.y = min(tl.y, (float) y);
        br.x = max(br.x, (float) x + keyW);
        br.y = max(br.y, (float) y + keyH);

        
        if (keys[i]->getName() == " ") {
            keys[i]->resize(keyW, keyH);
            keys[i]->setPosition(x, y);
        } else {
            keys[i]->resize(keyW, keyH);
            keys[i]->setPosition(x, y);
        }
    }
    
    bgRect.set(tl.x - 2*margin, tl.y - 2*margin, br.x-tl.x + 4*margin, br.y-tl.y + 4*margin);
    
    
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::draw() {
    if (!visible) return;
    
    ofPushStyle();
    ofSetColor(0, 185);
    ofDrawRectangle(bgRect);
    ofSetColor(255);
    for (int i=0; i<keys.size(); i++) {
        keys[i]->draw();
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::setUpperCase(bool upper) {
    for (int i=0; i<keys.size(); i++) {
        keys[i]->setUpperCase(upper);
    }
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::keyClicked(string & key) {
    if (key=="<") {
        input = input.substr(0, input.size()-1);
    } else {
        input += key;
    }

    bool toUpper = input.size() == 0 || input.substr(input.size()-1, input.size()) == " ";
    setUpperCase(toUpper);
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::drawInput() {
    if (!visible) return;
    
    int x = 100;
    int y = 100;
    
    font.drawString(input, x, y);
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::mouseMoved(int x, int y) {
    if (!visible) return;
    for (int i=0; i<keys.size(); i++) {
        keys[i]->mouseMoved(x, y);
    }
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::mouseDragged(int x, int y) {
    if (!visible) return;
    for (int i=0; i<keys.size(); i++) {
        keys[i]->mouseDragged(x, y);
    }

}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::mousePressed(int x, int y) {
    if (!visible) return;
    for (int i=0; i<keys.size(); i++) {
        keys[i]->mousePressed(x, y);
    }
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::mouseReleased(int x, int y) {
    if (!visible) return;
    for (int i=0; i<keys.size(); i++) {
        keys[i]->mouseReleased(x, y);
    }
}



