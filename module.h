#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "wire.h"

class Module {
	public:
		std::string name; // the user-defined name of the module, only for reference purpose
		std::string id; // the actual name of the module, according to verilog

		int max_connections; // there are a finite number of terminals

		std::vector<Wire&> connections; // each wire in the circuit has an integer identifier
		std::vector<int> conn_widths; // the bus width of each connection
		std::vector<int> conn_offsets; // specify where to start the range of bits of the connecting bus used
		
		std::vector<int> conn_positions; // each terminal needs a place to be drawn
		int symbol; // the image to draw
		int position; // where to draw the module

		Module(std::string _id, std::string _name, int _max_connections);

		bool operator==(const Module& other);
		void operator<<(std::ostream & os);
};