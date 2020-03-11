#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "wire.h"
#include "connection.hpp"

class Module {
	public:
		std::string name;		// the user-defined name of the module, only for reference purpose
		std::string id;			// the actual name of the module, according to verilog

		int max_connections;	// there are a finite number of terminals

		std::vector<Connection> connections;	// list of connections. SIZE IS CONSTANT.

		std::string symbol;				// the image to draw
		std::pair<int, int> position;	// where to draw the module
		Module(std::string _id, std::string _name, int _max_connections, std::vector<int> buswidths, std::vector<std::pair<int, int>> positions);
        Module(std::string _id, std::string _name, int _max_connections, std::vector<std::pair<int, int>> positions);
		Module() {};

		bool operator==(const Module& other);
		void operator<<(std::ostream & os);
};
