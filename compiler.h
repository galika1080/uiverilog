#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

#include "module.h"
#include "wire.h"

class Compiler {
	public:
		std::vector<Module*> mods;

		std::vector<Wire> wires;

		std::vector<Wire*> inputs;
		std::vector<Wire*> outputs;

	//public:
		std::string name;

		std::vector<Module*> getMods();

		void addMod(Module* m);
		void removeMod(Module* m);

		void compile(std::string filename);

		void connect(Module* first_module, int first_terminal, Module* second_module, int second_terminal, std::string wire_name);
		void connect(int first_ind, int first_terminal, int second_ind, int second_terminal, std::string wire_name);

		
		void setConnectionOffset(Module & module, int new_offset);

		void addOutput(std::string wire_name);
		void addInput(std::string wire_name);

		void sever(std::string wire_name);
		void removeOutput(std::string wire_name);
		void removeInput(std::string wire_name);

		//void sever(Module & first_module, Module & second_module, int first_terminal, int second_terminal);

		std::vector<Module*> getConnected(std::string wire_name);
};