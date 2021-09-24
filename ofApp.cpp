#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int v_span = 1;
	int u_span = 30;

	ofMesh face, line;
	ofColor color;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
	for (int v = 0; v <= 360; v += v_span) {

		bool flag = true;
		int u_start = v;
		int next_u = u_start + v_span;

		ofSeedRandom(39);
		for (int u = u_start; u < u_start + 360; u += u_span) {

			auto noise_param = ofRandom(1000);

			if (flag) {

				face.addVertex(this->make_point(230, 60, u, v));
				face.addVertex(this->make_point(230, 60, u + u_span, v));
				face.addVertex(this->make_point(230, 60, next_u + u_span, v + v_span));
				face.addVertex(this->make_point(230, 60, next_u, v + v_span));

				line.addVertex(this->make_point(230, 60, u, v));
				line.addVertex(this->make_point(230, 60, u + u_span, v));
				line.addVertex(this->make_point(230, 60, next_u + u_span, v + v_span));
				line.addVertex(this->make_point(230, 60, next_u, v + v_span));

				for (int i = 0; i < 4; i++) {

					color.setHsb((int)ofMap(ofNoise(glm::vec4(face.getVertex(face.getNumVertices() - 4 + i) * 0.0005, noise_param + ofGetFrameNum() * 0.003)), 0, 1, 0, 255 * 6) % 255, 130, 255);
					face.addColor(color);
					line.addColor(ofColor(239));
				}

				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

				line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 4);
				line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 3);
			}

			next_u += u_span;
		    flag = !flag;
		}
	}

	face.drawFaces();
	line.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}