#include "ofMain.h"
#include "ofApp.h"

int main( ){
	//ofSetupOpenGL(1024,768,OF_WINDOW);

	//ofRunApp(new ofApp());

	Compiler comp;

	std::vector<int> conns; conns.push_back(4); conns.push_back(20);
	Module m("and", "a1", conns);
	comp.addMod(m);

	comp.compile();
}
