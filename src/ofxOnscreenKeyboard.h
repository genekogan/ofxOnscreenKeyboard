#pragma once

#include "ofMain.h"
#include "ofxClickable.h"



//--------------------------------------------------------------
class ofxOnscreenKey : public ofxClickable {
public:
    void buttonClicked() {ofNotifyEvent(clickEvent, key, this);}
    void setKey(string key);
    void setUpperCase(bool upper);
    ofEvent<string> clickEvent;
    string key;
};


//--------------------------------------------------------------
class ofxOnscreenKeyboard {
public:
    ofxOnscreenKeyboard();
    
    void setup();
    void setPosition(int kX, int kY, int keyW, int keyH);
    
    void setUpperCase(bool upper);
    
    void draw();
    void drawInput();
  
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y);
    void mousePressed(int x, int y);
    void mouseReleased(int x, int y);
    
    void mouseMoved(ofMouseEventArgs & evt) {mouseMoved(evt.x, evt.y);}
    void mouseDragged(ofMouseEventArgs & evt) {mouseDragged(evt.x, evt.y);}
    void mousePressed(ofMouseEventArgs & evt) {mousePressed(evt.x, evt.y);}
    void mouseReleased(ofMouseEventArgs & evt) {mouseReleased(evt.x, evt.y);}
    
    void keyClicked(string & key);
    
    void setVisible(bool visible);
    bool getVisible() {return visible;}
    
protected:
    
    vector<ofxOnscreenKey*> keys;
    
    ofTrueTypeFont font;
    string input;
    
    
    ofRectangle bgRect;
    
    bool visible;
};


