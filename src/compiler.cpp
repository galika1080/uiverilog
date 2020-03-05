#include "compiler.h"

void Compiler::compile() {
	for (auto & mod : mods) {
		std::string out = mod.id + " " + mod.name + "("; // add the module ID and its user-defined name

		for (int i = 0; i < mod.connections.size()-1; i++) {
			out += "w" + std::to_string(mod.connections.at(i)) + ", "; // add every connection and then a comma (except the last)
			int conn = mod.connections.at(i);

			if (conn != -1) {
				out += "w" + std::to_string(conn) + ", "; // add every connection and then a comma (except the last)
			} else {
				out += ", ";
			}
		}
		
		int conn = mod.connections.back();

		if (conn != -1) {
			out += "w" + std::to_string(conn) + ");"; // add the last connection (no comma), close paren, semicolon
		} else {
			out += ");";
		}

		std::cout << out << std::endl;
	}
}

std::vector<Module>& Compiler::getMods() {
	return mods;
}

int Compiler::connect(Module & m1, Module & m2, int t1, int t2) {
	int new_num;
	for (new_num = 0; new_num < INT_MAX; new_num++) {
		if (!std::count(wires.begin(), wires.end(), new_num)) {
			break;
		}
	}
	// new_num is going to be the wire's identifier. It's just the lowest available one.

	wires.push_back(new_num); // take note that the wire exists
	m1.connections[t1] = new_num;
	m2.connections[t2] = new_num;

	return new_num;
}

std::vector<Module> Compiler::getConnected(int wire) {
	std::vector<Module> result;
	
	for (auto & mod : mods) {
		if (std::count(mod.connections.begin(), mod.connections.end(), wire)) {
			result.push_back(mod);
		}
	}

	return result;
}

void Compiler::sever(int wire) {
	for (auto & mod : mods) {
		if (int i = std::count(mod.connections.begin(), mod.connections.end(), wire)) {
			mod.connections[i] = -1; // -1 means a terminal is there, but not connected to anything
		}
	}

	for (int i = 0; i < wires.size(); i++) {
		if (wires[i] == wire) {
			wires.erase(wires.begin() + i);
		}
	}
}

void Compiler::addMod(Module m) {
	mods.push_back(m);
}

void Compiler::removeMod(Module& m) {
	for (int i = 0; i < mods.size(); i++) {
		if (mods[i] == m) {
			mods.erase(mods.begin() + i);
		}
	}
}
