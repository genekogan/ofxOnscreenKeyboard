#pragma once

#include "ofMain.h"
#include "ofxClickable.h"


//--------------------------------------------------------------
/*class ofxOnscreenKeyEvent : public ofEventArgs {
public:
    FaveButtonSettings settings;
    static ofEvent<FaveButtonEvent> events;
};*/

//--------------------------------------------------------------
class ofxOnscreenKey : public ofxClickable {
public:
    void buttonClicked() {ofNotifyEvent(clickEvent, key, this);}
    void setKey(string key){this->key = key;}
    ofEvent<string> clickEvent;
    string key;
};


class ofxOnscreenKeyboard {
public:
    ofxOnscreenKeyboard();
    void setup();
    
    void draw();
  
    
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y);
    void mousePressed(int x, int y);
    void mouseReleased(int x, int y);
    
    void mouseMoved(ofMouseEventArgs & evt) {mouseMoved(evt.x, evt.y);}
    void mouseDragged(ofMouseEventArgs & evt) {mouseDragged(evt.x, evt.y);}
    void mousePressed(ofMouseEventArgs & evt) {mousePressed(evt.x, evt.y);}
    void mouseReleased(ofMouseEventArgs & evt) {mouseReleased(evt.x, evt.y);}
    
    void keyClicked(string & key) {
        cout << "RCV " << key << endl;
    }
    
protected:
    
    vector<ofxOnscreenKey*> keys;
    
    ofTrueTypeFont font;
};


