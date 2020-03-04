#pragma once

#include <vector>
#include <iostream>

class Compiler {
	public:
		std::vector<Module> mods;

		void compile() {
			for (auto & mod : mods) {
				std::cout << mod << std::endl;
			}
		}
};