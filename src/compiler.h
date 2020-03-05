#pragma once

#include <vector>
#include <iostream>
#include "module.h"
#include <algorithm>

class Compiler {
	private:
		std::vector<Module> mods;
		std::vector<int> wires;

	public:
		std::vector<Module>& getMods();

		void addMod(Module m);
		void removeMod(Module & m);

		void compile();

		int connect(Module & first_module, Module & second_module, int first_terminal, int second_terminal);

		//void sever(Module & first_module, Module & second_module, int first_terminal, int second_terminal);

		std::vector<Module> getConnected(int wire);

		void sever(int wire);
};