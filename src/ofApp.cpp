#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(ofColor::white);
	
	initGame();
	
	ofSetFrameRate(2);
	
	ofSetWindowTitle("Minesweeper");
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	int x = 0, y = 0;
	for (auto column : boardOrigins) {
		y= 0;
		for (auto cellOrigin : column) {
			drawCell(cellOrigin, game->getCell(x, y));
			y++;
		}
		x++;
	}
	if (game->status == MinesweperGame::WON) {
		ofSetColor(ofColor::lightGreen);
		ofFill();
		ofDrawRectangle(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
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
	if (x < game->width * cellLength && y < game->height * cellLength) {
		int cellX;
		int cellY;
		int i = 0;
		while (1) {
			
			if (i*cellLength >=x) {
				cellX = i-1;
				break;
			}
			i++;
			
		}
		i = 0;
		while (1) {
			
			if (i*cellLength >=y) {
				cellY = i-1;
				break;
			}
			i++;
		}
		game->probeCell(cellX, cellY);
	}
	
	
	
	
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

void ofApp::exit() {
	endGame();
}

void ofApp::initGame(int height, int width, int mineCount) {
	game = new MinesweperGame(height, width, mineCount);
	cellLength = 50;
	
	for (int x = 0; x < width; x++) {
		boardOrigins.emplace_back(std::vector<ofPoint>());
		for (int y = 0; y < height; y++) {
			ofPoint cellOrigin;
			cellOrigin.set(x*cellLength, y*cellLength);
			boardOrigins[x].push_back(cellOrigin);
		}
	}
}

void ofApp::endGame() {
	delete game;
}

void ofApp::drawCell(ofPoint origin, int value) {
	// Draw Square
	ofNoFill();
	
	if (value == -2) {
		ofSetColor(ofColor::gray);
	} else if (value == -1) {
		ofSetColor(ofColor::red);
		ofFill();
	} else if (value == 0) {
		ofSetColor(ofColor::beige);
		ofFill();
	} else {
		ofSetColor(ofColor::lightBlue);
		ofFill();
	}
	ofRectangle cell(origin, cellLength, cellLength);
	ofDrawRectangle(cell);
	
	
	// draw label;
	if (value > 0) {
		ofSetColor(ofColor::black);
		ofPoint text;
		text.set(origin.x + (cellLength/2), origin.y + (cellLength/2));
		ofDrawBitmapString(std::to_string(value), text);
	}
	
}

