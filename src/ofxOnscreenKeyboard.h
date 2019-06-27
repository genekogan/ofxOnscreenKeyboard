#pragma once

#include "ofMain.h"
#include "ofxClickable.h"

//--------------------------------------------------------------
enum ofxOnscreenKeyboardLayout {
    LAYOUT_ENGLISH,
    LAYOUT_GERMAN
};

const vector<string> ofxOnscreenKeyboardUSEnglish =
    {"qwertyuiop", "asdfghjkl", "zxcvbnm."};

const vector<string> ofxOnscreenKeyboardGerman =
    {"qwertzuiopü", "asdfghjklöä", "yxcvbnm,."};


//--------------------------------------------------------------
class ofxOnscreenKey : public ofxClickable {
public:
    ofxOnscreenKey(int row, int keyWidth);
    void setUpperCase(bool upper);
    void setKey(string key);
    void buttonClicked() {ofNotifyEvent(clickEvent, key, this);}
    ofEvent<string> clickEvent;
    string key;
    int row;
    int keyWidth;
};


//--------------------------------------------------------------
class ofxOnscreenKeyboard {
public:
    ofxOnscreenKeyboard();
    ~ofxOnscreenKeyboard();

    void setup(ofxOnscreenKeyboardLayout layout);
    void setCharacterLimit(int characterLimit) {this->characterLimit = characterLimit;}
    void setPosition(int kX, int kY, int keyW, int keyH, int fontSize, int margin);
    void setMouseEventsAuto(bool automatic);
    
    void addKeys(string keys, int row, int width);
    void setUpperCase(bool upper);
    void clearInput() {input="";}
    
    string getInput() {return input;}
    
    void draw();
    void drawInput(int x, int y);
  
    bool mouseMoved(int x, int y);
    bool mouseDragged(int x, int y);
    bool mousePressed(int x, int y);
    bool mouseReleased(int x, int y);
    
    void mouseMoved(ofMouseEventArgs & evt) {mouseMoved(evt.x, evt.y);}
    void mouseDragged(ofMouseEventArgs & evt) {mouseDragged(evt.x, evt.y);}
    void mousePressed(ofMouseEventArgs & evt) {mousePressed(evt.x, evt.y);}
    void mouseReleased(ofMouseEventArgs & evt) {mouseReleased(evt.x, evt.y);}
    
    void keyClicked(string & key);
    
    void setVisible(bool visible);
    bool getVisible() {return visible;}
    void toggleVisible() {setVisible(!visible);}
    
protected:
    
    ofxOnscreenKeyboardLayout layout;
    vector<ofxOnscreenKey*> keys;
    ofTrueTypeFont font;
    ofRectangle bgRect;
    ofVec2f tl, br;
    string input;
    int margin;
    bool upper;
    bool visible;
    int characterLimit;
};


