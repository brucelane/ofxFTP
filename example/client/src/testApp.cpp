#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	client.setup("127.0.0.1", 5575);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if ( key == 's' ){
		client.sendFromOf("1.jpg", "Shared", "");
	}
	if ( key == 'k' ){
		client.getToOf("1.png", "", "");
	}

	if ( key == 'g' ){
		client.get("1.png", ofFilePath::getAbsolutePath("1.png"));
	}

	if ( key == 'l' ){
		vector<string> files = client.list("");
		for (int i = 0; i < files.size(); i++ )
		{
			cout<<files[i]<<endl;
		}
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
	if ( dragInfo.files.size() > 0 )
	{
		client.send(dragInfo.files[0], ofFilePath::getFileName(dragInfo.files[0]), false);
	}
}
