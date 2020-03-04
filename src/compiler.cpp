#include "compiler.h"

void Compiler::compile() {
	for (auto & mod : mods) {
		std::string out = mod.id + " " + mod.name + "("; // add the module ID and its user-defined name

		for (int i = 0; i < mod.connections.size()-1; i++) {
			out += "w" + std::to_string(mod.connections.at(i)) + ", "; // add every connection and then a comma (except the last)
		}
		
		out += "w" + std::to_string(mod.connections.back()) + ");"; // add the last connection (no comma), close paren, semicolon

		std::cout << out << std::endl;
	}
}

std::vector<Module>& Compiler::getMods() {
	return mods;
}

void Compiler::addMod(Module m) {
	mods.push_back(m);
}