#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(ofColor::white);
	
	initGame();
#if !defined(EMSCRIPTEN)
	ofSetFrameRate(24); // increases power + processor efficiency
#endif
	
	ofSetWindowTitle("Minesweeper");
	
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	int x = 0, y = 0;
	for (auto && column : boardOrigins) {
		y= 0;
		for (auto && cellOrigin : column) {
			drawCell(cellOrigin, game->getCell(x, y));
			y++;
		}
		x++;
	}
	if (game->status == MinesweperGame::WON && !lifted) {
		
		game->liftFog();
		lifted = true;
		
	}
	if (game->status == MinesweperGame::WON) {
		ofDrawBitmapString("You Win!", ofGetScreenWidth()/2, ofGetScreenHeight()/2);
	}
	ofDrawBitmapString(std::to_string(ofGetFrameRate()), 10, 10);
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
			//this is a comment
			
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
		try {
			game->probeCell(cellX, cellY);
		} catch (GameOver) {
			std::cout << "\nGame Over";
			endGame();
			initGame();
		} catch (InvalidCell) {
			std::cout << "\nInvalid Cell";
		}
		
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
	lifted = false;
	
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
	std::vector<std::vector<ofPoint>> empty;
	boardOrigins = empty;
	delete game;
}

void ofApp::drawCell(ofPoint origin, int value) {
	// Draw Square
	ofNoFill();
	
	if (value == -2) {
		ofSetColor(ofColor::gray);
	} else if (value == -1) {
		if (game->status == MinesweperGame::WON) {
			ofSetColor(ofColor::mistyRose);
		} else ofSetColor(ofColor::red);
		ofFill();
	} else if (value == 0) {
		ofSetColor(ofColor::beige);
		ofFill();
	} else {
		if (value == 1) {
			ofSetColor(ofColor::lightBlue);
		}
		if (value == 2) {
			ofSetColor(ofColor::lightGreen);
		}
		if (value == 3) {
			ofSetColor(ofColor::orange);
		}
		if (value == 4) {
			ofSetColor(ofColor::lightSalmon);
		}
		if (value == 5) {
			ofSetColor(ofColor::lightGoldenRodYellow);
		}
		if (value == 6) {
			ofSetColor(ofColor::chocolate);
		}
		if (value >=7) {
			ofSetColor(ofColor::moccasin);
		}
		
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

