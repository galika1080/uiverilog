#include "module.h"
#include <QDebug>

Module::Module(std::string _id, std::string _name, int _max_connections, std::vector<int> buswidths, std::vector<std::pair<int, int>> positions) {
	name = _name;
	id = _id;
	max_connections = _max_connections;
	
	for (int i = 0; i < _max_connections; i++) {
		Connection c(buswidths[i], positions[i]);
		connections.push_back(c);
	}
}

Module::Module(std::string _id, std::string _name, int _max_connections, std::vector<std::pair<int, int>> positions) {
	name = _name;
	id = _id;
	max_connections = _max_connections;
	
	for (int i = 0; i < _max_connections; i++) {
		Connection c(1, positions[i]);
		connections.push_back(c);
	}
}


bool Module::operator==(const Module& other) {
	return other.name == name && other.id == id;
}

void Module::operator<<(std::ostream& os) {
	os << id << " " << name;
}
