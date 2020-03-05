#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "ofxGui.h"

class Module {
	public:
		ofVec2f position; // where to draw the module
		std::string name; // the user-defined name of the module, only for reference purpose
		std::string id; // the actual name of the module, according to verilog
		int max_connections; // there are a finite number of terminals
		std::vector<int> connections; // each wire in the circuit has an integer identifier
		std::vector<ofVec2f> conn_positions; // each terminal needs a place to be drawn
		ofImage symbol; // the image to draw

		Module(std::string _id, std::string _name, int _max_connections);

		bool operator==(const Module& other);
		void operator<<(std::ostream & os);
};