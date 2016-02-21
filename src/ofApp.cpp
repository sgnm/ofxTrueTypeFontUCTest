#include "ofApp.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxTween.h"
#include "Lyrics.h"
#include "CircleAnimation.h"
#include "ImageSaver.h"

#define W 720
#define H 480
#define NUM 10
#define FROM 500
#define TO 0
#define DURATION 1000

//font
ofxTrueTypeFontUC myFont;
string sampleString;
vector<ofPath> characters;
vector<ofMesh> mesh;
vector<ofMesh> newMesh;
vector<int> ran;
ofPoint center;
Lyrics lyrics;
ofDirectory dir;
vector<string> fonts;

//tween
ofxTween tween;
ofxEasingQuint easing_bounce;
ofxTween transXtween;
ofxTween transYtween;
bool bSwitchFont;
bool bDrawCircle;
CircleAnimation circleAnim[NUM];

//capture
ImageSaver img;
int snapCounter;
string snapString;
bool bSnapshot;

//utils
string dirName;

//--------------------------------------------------------------
void ofApp::setup(){
    //font
//    myFont.loadFont("KozGoPr6N-ExtraLight.otf", 64, true, true);
    myFont.loadFont("ヒラギノ丸ゴ Pro W4.otf", 128, true, true);
    
    setupMesh();
    
    dir.listDir("");
    for(int i = 0; i < dir.size(); i++){
        fonts.push_back(dir.getName(i));
    }
    
    for (int i = 0; i < NUM; i++) {
        circleAnim[i].setup(lyrics.circleLyrics, 200, 200);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    if(bDrawCircle){
        for(int i = 0; i < NUM; i++){
            circleAnim[i].update(1.5);
        }
    }
    
    if(!bSwitchFont){
        for(int i = 0; i < mesh.size(); i++){
            for(int j = 0; j < mesh[i].getVertices().size(); j++){
                ofVec3f pos = newMesh[i].getVertices()[j] + ran[j];
                ofVec3f endPos = mesh[i].getVertices()[j];
                pos += (endPos - pos) * 0.2;
                newMesh[i].setVertex(j, pos);
            }
        }
    }
    
    if(ofGetFrameNum() % 5 == 0 && bSwitchFont){
        myFont.loadFont(fonts[ofRandom(0, fonts.size())], 128, true, true); //randomで
        mesh.clear();
        characters = myFont.getStringAsPoints(sampleString); //文字列の長さ取得
        center = ofPoint(myFont.stringWidth(sampleString)/2, myFont.stringHeight(sampleString)/2);
        
        for(int i = 0; i < characters.size(); i++){
            mesh.push_back(characters[i].getTessellation()); //文字をそれぞれメッシュ化し格納
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
    ofTranslate(W/2, H/2);
    if(bDrawCircle){
        for(int i = 0; i < NUM; i++){
            circleAnim[i].draw();
        }
    }
    ofTranslate(-center.x, center.y); //中心に移動
    ofTranslate(transXtween.update(), transYtween.update());
        for(int i = 0; i < mesh.size(); i++){
            if(bSwitchFont){
                mesh[i].drawWireframe();
            }else{
                newMesh[i].drawWireframe();
            }
        }
    ofPopMatrix();
    //draw------------------------------------------------
    
    //grab screen-----------------------------------------
    if(bSnapshot){
        img.grabScreen(0, 0, W, H);
        string fileName = dirName + "/" + ofToString(10000 + snapCounter) + ".png";
        img.saveThreaded(fileName);
        snapCounter++;
    }
    //grab screen-----------------------------------------
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'f') ofToggleFullscreen();
    if(key == 'r'){
        bSnapshot = true;
        ofDirectory dir;
        dirName = ofGetTimestampString("%Y%m%d%H%M%S");
        dir.createDirectory(dirName);
    }
    if(key == 's') bSnapshot = false;
    if(key == 'c') bDrawCircle = !bDrawCircle;
    if(key == 't'){
        transXtween.setParameters(1, easing_bounce, ofxTween::easeOut, ofRandom(-FROM, FROM), ofRandom(-100, 100), DURATION, 0);
        transYtween.setParameters(1, easing_bounce, ofxTween::easeOut, ofRandom(-FROM, FROM), ofRandom(-100, 100), DURATION, 0);
        setupMesh();
    }
    if(key == OF_KEY_RIGHT){
        transXtween.setParameters(1, easing_bounce, ofxTween::easeOut, FROM, TO, DURATION, 0);
        setupMesh();
    }
    if(key == OF_KEY_LEFT){
        transXtween.setParameters(2, easing_bounce, ofxTween::easeOut, -FROM, TO, DURATION, 0);
        setupMesh();
    }
    if(key == OF_KEY_UP){
        transYtween.setParameters(1, easing_bounce, ofxTween::easeOut, -FROM, TO, DURATION, 0);
        setupMesh();
    }
    if(key == OF_KEY_DOWN){
        transYtween.setParameters(2, easing_bounce, ofxTween::easeOut, FROM, TO, DURATION, 0);
        setupMesh();
    }
    if(key == OF_KEY_RETURN){
        setupMesh();
    }
    if(key == ' '){
        bSwitchFont = !bSwitchFont;
        if(!bSwitchFont){
            setupMesh();
        }
    }
}

//--------------------------------------------------------------
void ofApp::setupMesh(){
    mesh.clear();
    sampleString = lyrics.getNextString();
    characters = myFont.getStringAsPoints(sampleString); //文字列の長さ取得
    center = ofPoint(myFont.stringWidth(sampleString)/2, myFont.stringHeight(sampleString)/2);
    
    for(int i = 0; i < characters.size(); i++){
        mesh.push_back(characters[i].getTessellation()); //文字をそれぞれメッシュ化し格納
    }
    
    newMesh = mesh; //元mesh->変形する為のnewMeshにコピー
    
    //テキストアニメーションリセット処理
    ran.clear();
    for(int i = 0; i < mesh.size(); i++){
        for(int j = 0; j < mesh[i].getVertices().size(); j++){
            int n = ofRandom(-2, 2);
            ran.push_back(n);
            
            static float pi;
            float rad = ofRandom(300, 500);
            ofVec2f p = ofVec2f(rad * cos(pi), rad * sin(pi));
            newMesh[i].setVertex(j, mesh[i].getVertex(j) + ofVec3f(p.x, p.y, 0));
            pi += 0.01;
        }
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
