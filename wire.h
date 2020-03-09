#pragma once
#include <string>
#include <iostream>

struct Wire {
	std::string id;
	int width;

	Wire(std::string name, int bus_width) {
		id = name;
		width = bus_width;
	}

	Wire(std::string name) {
		id = name;
		width = 1;
	}

	bool operator==(Wire rhs) {
		return id == rhs.id;
	}

    void operator<<(std::ostream o) {
		o << id << ", width " << width << ", address " << this;
	}
};
