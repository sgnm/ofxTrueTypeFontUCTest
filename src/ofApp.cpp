#include "ofApp.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxTween.h"

//font
ofxTrueTypeFontUC myFont;
string sampleString;
vector<ofPath> characters;
vector<ofMesh> mesh;
vector<ofMesh> newMesh;
vector<int> ran;

//tween
ofxTween tween;
ofxEasingQuint easing_bounce;

//--------------------------------------------------------------
void ofApp::setup(){
    //font
//    myFont.loadFont("KozGoPr6N-ExtraLight.otf", 64, true, true);
    myFont.loadFont("ヒラギノ丸ゴ Pro W4.otf", 128, true, true);
    
    sampleString = "あいうえお";
    characters = myFont.getStringAsPoints(sampleString); //文字列の長さ取得
    
    for(int i = 0; i < characters.size(); i++){
        mesh.push_back(characters[i].getTessellation()); //文字をそれぞれメッシュ化し格納
        for(int j = 0; j < mesh[i].getVertices().size(); j++){
            int n = ofRandom(-10, 10);
            ran.push_back(n);
        }
    }
    
    newMesh = mesh; //元mesh->変形する為のnewMeshにコピー
    
    //tween
    tween.setParameters(1,easing_bounce, ofxTween::easeOut, 2.0, 1.0, 1000, 500);
}

//--------------------------------------------------------------
void ofApp::update(){
    tween.update();
    
    for(int i = 0; i < mesh.size(); i++){
        for(int j = 0; j < mesh[i].getVertices().size(); j++){
            ofVec3f v = newMesh[i].getVertices()[j];
            v = v * tween.getTarget(0) + ran[j];
            mesh[i].setVertex(j, v);
        }
    }

    //アニメーションリセット処理
    if(tween.isCompleted() && ofGetFrameNum() % 120 == 0){
        tween.setParameters(1,easing_bounce, ofxTween::easeOut, 10.0, 1.0, 500, 500);
        ran.clear();
        for(int i = 0; i < mesh.size(); i++){
            for(int j = 0; j < mesh[i].getVertices().size(); j++){
                int n = ofRandom(-10, 10);
                ran.push_back(n);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    string fpsStr = "frame rate: " + ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapStringHighlight(fpsStr, 20, 20);
    
    //draw------------------------------------------------
    ofPushMatrix();
    ofTranslate(100, 300);
        for(int i = 0; i < mesh.size(); i++){
            mesh[i].drawVertices();
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
