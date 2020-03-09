#pragma once
#include "wire.h"
#include <iostream>
#include <QDebug>

struct Connection {
    bool enabled;                   // connected or not
	Wire * wire;                    // the connected wire

	int width;                      // the width of the bus. CANNOT be changed.
	int offset;                     // the starting bit of the bus. CAN be changed.

	std::pair<int, int> position;   // where to draw connection in workspace

    Connection(int bus_width, std::pair<int, int> draw_position) {
        enabled = false;
        wire = nullptr;
        width = bus_width;
        offset = 0;
        position = draw_position;
    }

    void reset() { // disconnects, disables, and sets offset to zero
        enabled = false;
        wire = nullptr;
        offset = 0;
    }

    void operator<<(std::ostream o) {
        o << "connection enabled: " << std::to_string(enabled) << "; connected wire: " << wire << "[" << std::to_string(width+offset-1) << ":" << std::to_string(offset) << "]";
    }

    bool operator==(Connection rhs) { // to find by ID, use a dummy Connection with width -1, on LHS
        if (!enabled || !rhs.enabled) {
            return false;
        }
        
        if (rhs.width == -1) { // this is for find-by-ID
            return wire->id == rhs.wire->id;
        }

        return wire->id == rhs.wire->id && width == rhs.width && offset == rhs.offset;
    }
};
