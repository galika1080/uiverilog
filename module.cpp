#include "module.h"
#include <QDebug>

/*Module::Module(std::string _id, std::string _name, int _max_connections, std::vector<int> buswidths, std::vector<std::pair<int, int>> positions) {
	name = _name;
	id = _id;
	max_connections = _max_connections;

	for (int i = 0; i < _max_connections; i++) {
		connections.push_back(Connection(buswidths[i], positions[i]));

		Connection c{1, std::pair<int, int>(0, 0)};
		connections.push_back(c);
	}
}*/

Module::Module(std::string _id, std::string _name, int _max_connections, std::vector<std::pair<int, int>> positions) {
	name = _name;
	id = _id;
	max_connections = _max_connections;
	
	for (int i = 0; i < _max_connections; i++) {
		positions.push_back(std::pair<int, int>(0, 0));

		Connection c(1, std::pair<int, int>(0, 0));
		connections.push_back(c);
	}
}


bool Module::operator==(const Module& other) {
	return other.name == name && other.id == id;
}

void Module::operator<<(std::ostream& os) {
	os << id << " " << name;
}
