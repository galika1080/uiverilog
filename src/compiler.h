#pragma once

#include <vector>
#include <iostream>
#include "module.h"

class Compiler {
	private:
		std::vector<Module> mods;
	public:
		void addMod(Module m);
		void compile();
		std::vector<Module> & getMods();
};