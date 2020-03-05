#include "module.h"

Module::Module(std::string _id, std::string _name, int _max_connections) {
	name = _name;
	id = _id;
	max_connections = _max_connections;

	for (int i = 0; i < _max_connections; i++) {
		connections.push_back(-1); // -1 represents a disconnected terminal
	}
}


bool Module::operator==(const Module& other) {
	return other.name == name && other.id == id;
}

void Module::operator<<(std::ostream& os) {
	os << id << " " << name;
}
