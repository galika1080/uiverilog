#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

#include "module.h"
#include "wire.h"

class Compiler {
	private:
		std::vector<Module> mods;
		std::vector<int> wires;
		std::vector<int> inputs;
		std::vector<int> outputs;

	public:
		std::string name;

		std::vector<Module>& getMods();

		void addMod(Module m);
		void removeMod(Module & m);

		void compile(std::string filename);

		int connect(Module & first_module, Module & second_module, int first_terminal, int second_terminal);
		void addOutput(int wire);
		void addInput(int wire);

		void sever(int wire);
		void removeOutput(int wire);
		void removeInput(int wire);

		//void sever(Module & first_module, Module & second_module, int first_terminal, int second_terminal);

		std::vector<Module> getConnected(int wire);
};