#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    ofSetVerticalSync(true);
    ofBackground(20);
    float width	 = ofGetWidth() * .12;
    float height	= ofGetHeight() * .12;

    icoSphere.setRadius( width );


    ofSetSmoothLighting(true);

    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));

    pointLight2.setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
    pointLight2.setSpecularColor(ofFloatColor(.8f, .8f, .9f));

    pointLight3.setDiffuseColor( ofFloatColor(19.f/255.f,94.f/255.f,77.f/255.f) );
    pointLight3.setSpecularColor( ofFloatColor(18.f/255.f,150.f/255.f,135.f/255.f) );

    // shininess is a value between 0 - 128, 128 being the most shiny //
    material.setShininess( 120 );
    // the light highlight of the material //
    material.setSpecularColor(ofColor(255, 255, 255, 255));

//    icoSphere.setMode( OF_PRIMITIVE_TRIANGLES );

    icoSphere.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    icoSphere.setResolution(1);
}
//--------------------------------------------------------------
void ofApp::update(){
    pointLight.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight()/2, 500);
    pointLight2.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.15)*(ofGetWidth()*.3),
                            ofGetHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(ofGetHeight()), -300);

    pointLight3.setPosition(
            cos(ofGetElapsedTimef()*1.5) * ofGetWidth()*.5,
            sin(ofGetElapsedTimef()*1.5f) * ofGetWidth()*.5,
            cos(ofGetElapsedTimef()*.2) * ofGetWidth()
            );
}

//--------------------------------------------------------------
void ofApp::draw(){
    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);

    if (bMousePressed) {
        spinX = spinY = 0.0f;
    }

    cam.setGlobalPosition({ 0,0,cam.getImagePlaneDistance(ofGetCurrentViewport()) });
    cam.begin();

    ofEnableDepthTest();

    ofEnableLighting();
    pointLight.enable();
    pointLight2.enable();
    pointLight3.enable();



    // draw the outer sphere
    material.begin();
    ofNoFill();
    ofDrawSphere(0, 0, max(ofGetWidth(),ofGetHeight()));
    material.end();

    float screenWidth = ofGetWidth();
    float screenHeight = ofGetHeight();

    icoSphere.setPosition( -screenWidth * .5 + screenWidth *  2/4.f, screenHeight * -0.5/6.f, 0);

    // ICO Sphere //
    icoSphere.rotateDeg(spinX, 1.0, 0.0, 0.0);
    icoSphere.rotateDeg(spinY, 0, 1.0, 0.0);

//    mode = 3;
//    if (mode == 3) {
//        triangles = icoSphere.getMesh().getUniqueFaces();
//    }

    bool bFill = true;
    if (bFill) {
        material.begin();
        ofFill();
//        sphere.setMode( OF_PRIMITIVE_TRIANGLES );
//        vector<ofMeshFace> triangles = sphere.getMesh().getUniqueFaces();
//        sphere.getMesh().setFromTriangles( triangles, true );
        //mode == 3
        if (true) {
            triangles = icoSphere.getMesh().getUniqueFaces();
            icoSphere.getMesh().setFromTriangles(triangles, true);
            float angle = (ofGetElapsedTimef() * 1.4);
            glm::vec3 faceNormal;
            for (size_t i = 0; i < triangles.size(); i++) {
                float frc = ofSignedNoise(angle* (float)i * .01, angle*.05) * 2.75;
                faceNormal = triangles[i].getFaceNormal();
                for (int j = 0; j < 3; j++) {
                    triangles[i].setVertex(j, triangles[i].getVertex(j) + faceNormal * frc);
                }
            }
            icoSphere.getMesh().setFromTriangles(triangles);
        }

        icoSphere.draw();
        material.end();
    }

    bool bWireframe = true;
    if (bWireframe) {
        ofNoFill();
        ofSetColor(0, 0, 0);
        icoSphere.setScale(1.01f);
        icoSphere.drawWireframe();
        icoSphere.setScale(1.f);
    }

    bool bDrawLights = true;

    if (bDrawLights) {
        ofFill();
        ofSetColor(pointLight.getDiffuseColor());
        pointLight.draw();
        ofSetColor(pointLight2.getDiffuseColor());
        pointLight2.draw();
        ofSetColor(pointLight3.getDiffuseColor());
        pointLight3.draw();
    }



    ofDisableDepthTest();

    cam.end();

    ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);

    ofDrawBitmapStringHighlight("ofIcoSpherePrimitive", glm::vec3(-90,+160,0) + cam.worldToScreen( icoSphere.getPosition()));

    if(true) {
        stringstream ss;
        ss << "FPS: " << ofToString(ofGetFrameRate(),0) << endl << endl;
        ss << "(f): Toggle Fullscreen"<<endl<<"(s): Draw Solid Shapes"<<endl<<"(w): Draw Wireframes"<<endl;
        ss <<"(1/2/3/4): Set Resolutions" <<endl<<"(n): Draw Normals"<<"\n(LEFT/RIGHT): Set Mode "<<ofToString(mode,0)<<endl;
        ss <<"(z): Split Faces " <<bSplitFaces<<endl;
        ss <<"(a): Draw Axes"<<endl<<"(l): Render lights" << endl <<"(h): Toggle help."<<endl;
        ofDrawBitmapStringHighlight(ss.str().c_str(), 20, 20);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
    bMousePressed = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    bMousePressed = false;
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
