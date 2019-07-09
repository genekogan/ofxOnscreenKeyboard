#include "ofxOnscreenKeyboard.h"


//--------------------------------------------------------------
ofxOnscreenKey::ofxOnscreenKey(int row, int keyWidth) {
    this->row = row;
    this->keyWidth = keyWidth;
}

//--------------------------------------------------------------
void ofxOnscreenKey::setKey(string key) {
    this->key = key;
    setName(key);
}

//--------------------------------------------------------------
void ofxOnscreenKey::setUpperCase(bool upper) {
    if (key == "ö" && upper) { setKey("Ö"); }
    else if (key == "Ö" && !upper) { setKey("ö"); }
    else if (key == "ü" && upper) { setKey("Ü"); }
    else if (key == "Ü" && !upper) { setKey("ü"); }
    else if (key == "ä" && upper) { setKey("Ä"); }
    else if (key == "Ä" && !upper) { setKey("ä"); }
    else { setKey(upper ? ofToUpper(key) : ofToLower(key)); }
}

//--------------------------------------------------------------
ofxOnscreenKeyboard::ofxOnscreenKeyboard() {
    visible = true;
    upper = false;
    characterLimit = 1e8;
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::setMouseEventsAuto(bool automatic) {
    if (automatic) {
        ofAddListener(ofEvents().mouseMoved, this, &ofxOnscreenKeyboard::mouseMoved);
        ofAddListener(ofEvents().mousePressed, this, &ofxOnscreenKeyboard::mousePressed);
        ofAddListener(ofEvents().mouseDragged, this, &ofxOnscreenKeyboard::mouseDragged);
        ofAddListener(ofEvents().mouseReleased, this, &ofxOnscreenKeyboard::mouseReleased);
    }
    else {
        ofRemoveListener(ofEvents().mouseMoved, this, &ofxOnscreenKeyboard::mouseMoved);
        ofRemoveListener(ofEvents().mousePressed, this, &ofxOnscreenKeyboard::mousePressed);
        ofRemoveListener(ofEvents().mouseDragged, this, &ofxOnscreenKeyboard::mouseDragged);
        ofRemoveListener(ofEvents().mouseReleased, this, &ofxOnscreenKeyboard::mouseReleased);
    }
}

//--------------------------------------------------------------
ofxOnscreenKeyboard::~ofxOnscreenKeyboard() {
    for (auto k : keys) {
        delete k;
    }
    keys.clear();
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::addKeys(string keyRow, int row, int width) {
    bool umlaut = false;
    for (char & c : keyRow) {
        string keyStr = ofToString(c);
        if (keyStr == "\303") {
            umlaut = true;
            continue;
        } else if (keyStr == "\274" && umlaut) {
            keyStr = "ü";
            umlaut = false;
        } else if (keyStr == "\266" && umlaut) {
            keyStr = "ö";
            umlaut = false;
        } else if (keyStr == "\244" && umlaut) {
            keyStr = "ä";
            umlaut = false;
        }
        ofxOnscreenKey *key = new ofxOnscreenKey(row, width);
        key->setup(keyStr, 0, 0, 1, 1);
        key->setKey(keyStr);
        key->setFont(&font);
        key->setBackgroundColor(ofColor::lightGray);
        key->setBackgroundGradient(85);
        key->setCornerRounded(10);
        keys.push_back(key);
        ofAddListener(key->clickEvent, this, &ofxOnscreenKeyboard::keyClicked);
    }
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::setup(ofxOnscreenKeyboardLayout layout) {
    this->layout = layout;
    
    tl.set(1e8, 1e8);
    br.set(-1e8, -1e8);
    
    if (layout == LAYOUT_ENGLISH) {
        addKeys(ofxOnscreenKeyboardUSEnglish[0], 0, 1);
        addKeys(ofxOnscreenKeyboardUSEnglish[1], 1, 1);
        addKeys(ofxOnscreenKeyboardUSEnglish[2], 2, 1);
    }
    else if (layout == LAYOUT_GERMAN) {
        addKeys(ofxOnscreenKeyboardGerman[0], 0, 1);
        addKeys(ofxOnscreenKeyboardGerman[1], 1, 1);
        addKeys(ofxOnscreenKeyboardGerman[2], 2, 1);
    }
    addKeys("^", 3, 2);
    addKeys(" ", 3, 7);
    addKeys("<", 3, 2);
    
    setUpperCase(true);
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::setVisible(bool visible) {
    this->visible = visible;
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::setPosition(int kX, int kY, int keyW, int keyH, int fontSize, int margin) {
    this->margin = margin;
    font.load("verdana.ttf", fontSize, true, true);
    
    vector<float> rowX = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    rowX[0] += 0 * keyW;
    rowX[1] += 0.333 * keyW;
    rowX[2] += 0.666 * keyW;
    rowX[3] += 0.333 * keyW;
    rowX[4] += 0 * keyW;
    rowX[5] += 0.333 * keyW;
    rowX[6] += 0.666 * keyW;
    rowX[7] += 0.333 * keyW;
    rowX[8] += 0 * keyW;
    rowX[9] += 0.333 * keyW;
    
    for (int i=0; i<keys.size(); i++) {
        int r = keys[i]->row;
        int w = keys[i]->keyWidth;
        
        int x = kX + rowX[r];
        int y = kY + r * (keyH + margin);

        rowX[r] += (w * keyW + margin);

        keys[i]->resize(w * keyW, keyH);
        
        if (keys[i]->key == "<") {
            keys[i]->loadIcon("backspace.png");
        } else if (keys[i]->key == "^") {
            keys[i]->loadIcon("shift.png");
        }
        
        keys[i]->setPosition(x, y);

        tl.x = min(tl.x, (float) x);
        tl.y = min(tl.y, (float) y);
        br.x = max(br.x, (float) x + keyW);
        br.y = max(br.y, (float) y + keyH);
    }
    
    bgRect.set(tl.x - 2*margin, tl.y - 2*margin, br.x-tl.x + 4*margin, br.y-tl.y + 4*margin);
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::draw() {
    if (!visible) return;
    int rectMargin = 5;
    ofPushStyle();
//    ofSetColor(0, 225);
//    ofNoFill();
//    ofSetLineWidth(rectMargin*2);
//    ofDrawRectRounded(bgRect.getX()-rectMargin,
//                      bgRect.getY()-rectMargin,
//                      bgRect.getWidth()+2*rectMargin,
//                      bgRect.getHeight()+2*rectMargin, 20);
    ofFill();
    ofSetColor(20, 185);
    ofDrawRectRounded(bgRect, 20);
    ofSetColor(255);
    for (int i=0; i<keys.size(); i++) {
        keys[i]->draw();
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::setUpperCase(bool upper) {
    this->upper = upper;
    for (int i=0; i<keys.size(); i++) {
        keys[i]->setUpperCase(upper);
    }
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::keyClicked(string & key) {
    if (key=="<") {
        input = input.substr(0, input.size()-1);
    } else if (key=="^") {
        setUpperCase(!upper);
    } else {
        if (input.size() < characterLimit) {
            input += key;
        }
        bool toUpper = input.size() == 0 || input.substr(input.size()-1, input.size()) == " ";
        setUpperCase(toUpper);
    }
}

//--------------------------------------------------------------
void ofxOnscreenKeyboard::drawInput(int x, int y) {
    if (!visible) return;
    font.drawString(input, x, y);
}

//--------------------------------------------------------------
bool ofxOnscreenKeyboard::mouseMoved(int x, int y) {
    if (!visible) return false;
    for (int i=0; i<keys.size(); i++) {
        keys[i]->mouseMoved(x, y);
    }
    return bgRect.inside(x, y);
}

//--------------------------------------------------------------
bool ofxOnscreenKeyboard::mouseDragged(int x, int y) {
    if (!visible) return false;
    for (int i=0; i<keys.size(); i++) {
        keys[i]->mouseDragged(x, y);
    }
    return bgRect.inside(x, y);
}

//--------------------------------------------------------------
bool ofxOnscreenKeyboard::mousePressed(int x, int y) {
    if (!visible) return false;
    for (int i=0; i<keys.size(); i++) {
        keys[i]->mousePressed(x, y);
    }
    return bgRect.inside(x, y);
}

//--------------------------------------------------------------
bool ofxOnscreenKeyboard::mouseReleased(int x, int y) {
    if (!visible) return false;
    for (int i=0; i<keys.size(); i++) {
        keys[i]->mouseReleased(x, y);
    }
    return bgRect.inside(x, y);
}

