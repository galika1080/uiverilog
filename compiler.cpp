#include "compiler.h"
#include <QDebug>

void Compiler::compile(std::string filename) {
	std::ofstream output;
	output.open(filename);

	for (auto & wire : outputs) {
		std::string out = "output ";
		if (wire->width != 1) {
			out += "[" + std::to_string(wire->width-1) + ":0] "; // specify width if it's not 1
		}
		out += wire->id + ";";

		output << out << std::endl; // write to file, one wire at a time, seperate lines
	}

	for (auto & wire : inputs) {
		std::string out = "input ";
		if (wire->width != 1) {
			out += "[" + std::to_string(wire->width-1) + ":0] "; // specify width if it's not 1
		}
		out += wire->id + ";";

		output << out << std::endl; // write to file, one wire at a time, seperate lines
	}

	for (auto & wire : wires) {	// deal with wires
		
		if (std::count(outputs.begin(), outputs.end(), wire) || std::count(inputs.begin(), inputs.end(), wire)) {
			continue; // if this wire is an output or an input, don't print it again
		}

		std::string out = "wire ";
		if (wire->width != 1) {
			out += "[" + std::to_string(wire->width-1) + ":0] "; // specify width if it's not 1
		}
		out += wire->id + ";";

		output << out << std::endl; // write to file, one wire at a time, seperate lines
	}

	output << std::endl; // seperate wires from modules for readability

	for (auto & mod : mods) {
		std::string out = mod->id + " " + mod->name + "("; // add the module ID and its user-defined name

		for (auto & conn : mod->connections) {
			if (conn.enabled) {
				out += conn.wire->id; // add the wire's name

				if (conn.width != conn.wire->width) { // if it's not 1-bit wide, specify which bits to use
					out += "[" + std::to_string(conn.width + conn.offset - 1) + ":" + std::to_string(conn.offset) + "]";
				}
			}
			out += ", "; // even if it's not connected to anything, we need to acknowledge its existence
		}

		out.pop_back();
		out.pop_back();
		out += ");";

		output << out << std::endl;
	}

	output << "endmodule //" << filename << std::endl;
	output.close();
}

std::vector<Module*> Compiler::getMods() {
	return mods;
}

void Compiler::connect(int i1, int t1, int i2, int t2, std::string id) {
	connect(mods[i1], t1, mods[i2], t2, id);
}

void Compiler::connect(Module* m1, int t1, Module* m2, int t2, std::string id) {
	for (auto & wire : wires) {
		if (wire->id == id) return; // we can't have two wires with the same identifiers
	}

	Connection & c1 = m1->connections[t1];
	Connection & c2 = m2->connections[t2];

	if (c1.enabled)	{
		sever(c1.wire->id);
	}
	if (c2.enabled) {
		sever(c2.wire->id);
	}
	
	int width = std::min(c1.width, c2.width);
	wires.push_back(new Wire(id, width));

	c1.enabled = true;
	c2.enabled = true;
	c1.wire = wires.back();
	c2.wire = wires.back();
}

void Compiler::addOutput(std::string id) {
	auto existing_wire = std::find_if(wires.begin(), wires.end(), CompareWirePointers(new Wire(id)));
	if (existing_wire != wires.end()) {
        outputs.push_back(*existing_wire);
	}
}

void Compiler::removeOutput(std::string id) {
    auto existing_wire_iter = std::find_if(outputs.begin(), outputs.end(), CompareWirePointers(new Wire(id)));
	if (existing_wire_iter != outputs.end()) {
    	outputs.erase(std::find(outputs.begin(), outputs.end(), *existing_wire_iter));
	}
}

void Compiler::addInput(std::string id) {
	auto existing_wire = std::find_if(wires.begin(), wires.end(), CompareWirePointers(new Wire(id)));
	if (existing_wire != wires.end()) {
        inputs.push_back(*existing_wire);
	}
}

void Compiler::removeInput(std::string id) {
    auto existing_wire_iter = std::find_if(inputs.begin(), inputs.end(), CompareWirePointers(new Wire(id)));
	if (existing_wire_iter != inputs.end()) {
    	inputs.erase(std::find(inputs.begin(), inputs.end(), *existing_wire_iter));
	}
}

std::vector<Module*> Compiler::getConnected(std::string id) {
	std::vector<Module*> result;

	Connection find_this(-1, std::pair<int,int>(-1, -1));
	find_this.wire = new Wire(id);
	find_this.enabled = true;
	
	for (auto & mod : mods) {
		if (std::find(mod->connections.begin(), mod->connections.end(), find_this) != mod->connections.end()) { // may need to flip around operator== for Connection
			if (!std::count(result.begin(), result.end(), mod)) {
				result.push_back(mod);
			}
		}
	}

	delete find_this.wire;

	return result;
}

void Compiler::sever(std::string id) {
	std::vector<Module*> connected = getConnected(id);

	for (auto & mod : connected) {
		for (auto & conn : mod->connections) {
			if (conn.enabled && conn.wire->id == id) {
				conn.reset();
			}
		}
	}

	auto found_iter = std::find_if(wires.begin(), wires.end(), CompareWirePointers(new Wire(id)));
	if (found_iter != wires.end()) {
		wires.erase(found_iter);
	}

	removeOutput(id);
	removeInput(id);
}

void Compiler::addMod(Module* m) {
	mods.push_back(m);
}

void Compiler::removeMod(Module* m) {
	for (int i = 0; i < mods.size(); i++) {
		if (mods[i] == m) {
			// find some way to manage destroyed connections...
			delete mods[i];
			mods.erase(mods.begin() + i);
		}
	}
}
