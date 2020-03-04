#pragma once
#include <vector>
#include <string>
#include "ofxGui.h"

class Module {
	public:
		ofVec2f position;
		std::string name;
		std::string id;
		std::vector<int> connections; // each wire in the circuit has an integer identifier
		std::vector<ofVec2f> conn_positions; // each terminal needs a place to be drawn

		Module(std::string _id, std::string _name, std::vector<int> conn);
};