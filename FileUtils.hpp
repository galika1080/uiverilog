#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "assert.h"
#include "module.h"

class FileUtils {
    public:
    static void ModuleToFile(Module & m, std::string filename) {
        std::ofstream file;
        file.open(filename);

        // write the basic info
        file << "<moduleinfo>"			<< std::endl;
		file << m.id					<< std::endl;
        file << m.symbol				<< std::endl;
		file << m.max_connections		<< std::endl;

		for (auto & c : m.connections) {
			file << "<connection>"		<< std::endl;
			file << c.width				<< std::endl;
			file << c.position.first 	<< std::endl;
			file << c.position.second	<< std::endl;
			file << "</connection>"		<< std::endl;
		}

		file << "</moduleinfo>"			<< std::endl;
		file.close();
    }

	static std::vector<Module*> ModulesFromFile(std::string filename) {
		std::vector<Module*> mods;
		
		std::ifstream file;
		file.open(filename);
		std::string line; // this is always just a temporary to look for the open and close symbols

		while (getline(file, line)) { // check if there's a line at all
			Module* m = new Module();

            while (line != "<moduleinfo>") {
                getline(file, line);
            }

			if (line == "<moduleinfo>") { // get basic module info
				getline(file, m->id);
				getline(file, m->symbol);
				std::string max_conn; getline(file, max_conn);
				m->max_connections = std::stoi(max_conn);

				getline(file, line); // update temp so we can see what to do next
			}

			while (line == "<connection>") { // do each connection
				std::string width;	getline(file, width);
				std::string first;	getline(file, first);
				std::string second;	getline(file, second);

				Connection c(std::stoi(width), std::pair<int,int>(std::stoi(first), std::stoi(second)));
				m->connections.push_back(c);

				getline(file, line);
				assert(line == "</connection>"); // if this isn't here... we're screwed.
				getline(file, line); // update temp again...
			}

            if (line == "</moduleinfo>") {
				mods.push_back(m);
			}
		}

		file.close();

		return mods;
	}
};
