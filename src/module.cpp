#include "module.h"

Module::Module(std::string _id, std::string _name, std::vector<int> conn) {
	name = _name;
	id = _id;
	connections = conn;
}
