#include "ofApp.h"
#include "ofxTrueTypeFontUC.h"

ofxTrueTypeFontUC myFont;
string sampleString;
vector<ofPath> characters;
vector<ofMesh> mesh;

//--------------------------------------------------------------
void ofApp::setup(){
//    myFont.loadFont("KozGoPr6N-ExtraLight.otf", 64, true, true);
    myFont.loadFont("ヒラギノ丸ゴ Pro W4.otf", 128, true, true);
    
    sampleString = "あいうえお";
    characters = myFont.getStringAsPoints(sampleString); //文字列の長さ取得
    
    for(int i = 0; i < characters.size(); i++){
        mesh.push_back(characters[i].getTessellation()); //文字をそれぞれメッシュ化し格納
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    string fpsStr = "frame rate: " + ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapStringHighlight(fpsStr, 20, 20);
    
    //draw------------------------------------------------
    ofPushMatrix();
    ofTranslate(100, 300);
        for(int i = 0; i < mesh.size(); i++){
            mesh[i].draw();
            ofTranslate(0, 300);
            mesh[i].drawWireframe();
            ofTranslate(100, -300);
        }
    ofPopMatrix();
    //draw------------------------------------------------
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'f') ofToggleFullscreen();
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
